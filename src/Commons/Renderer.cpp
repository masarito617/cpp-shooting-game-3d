#include "Renderer.h"
#include "../Game.h"
#include "../Actors/Camera.h"
#include "../Components/SpriteComponent.h"
#include "../Components/MeshComponent.h"
#include "../Commons/VertexArray.h"
#include "../Commons/Texture.h"
#include "../Commons/Mesh.h"

Renderer::Renderer(class Game *game)
:mGame(game)
,mWindow(nullptr)
,mAmbientLight(Math::VEC3_ZERO)
,mDirLightDirection(Math::VEC3_ZERO)
,mDirLightDiffuseColor(Math::VEC3_ZERO)
,mDirLightSpecColor(Math::VEC3_ZERO)
,m2DSpriteShader(nullptr)
,m2DSpriteVertexArray(nullptr)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize()
{
    // SDL関連初期化
    if (!InitSDL())
    {
        SDL_Log("%s", SDL_GetError());
        return false;
    }

    // GLEWの初期化
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) return false;
    glGetError();

    return true;
}

bool Renderer::InitSDL()
{
    // 初期化に失敗したらfalseを返す
    bool success = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0;
    if (!success) return false;

    // OpenGL設定
    // コアOpenGLプロファイル
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // バージョン3.3を指定
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // RGBA各チャネル8ビットのカラーバッファ
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Zバッファのビット数
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    // ダブルバッファ
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // ハードウェアアクセラレーション
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // OpenGLウィンドウの作成
    mWindow = SDL_CreateWindow("ShootingGame3D",
                               100, 100,mGame->ScreenWidth, mGame->ScreenHeight,
                               SDL_WINDOW_OPENGL);
    if (!mWindow) return false;

    // OpenGLコンテキストの作成
    mContext = SDL_GL_CreateContext(mWindow);
    if (!mContext) return false;

    return true;
}

bool Renderer::LoadData()
{
    // ビュー射影座標を設定
    mViewMatrix = Matrix4::CreateLookAt(Math::VEC3_ZERO, Math::VEC3_UNIT_Z, Math::VEC3_UNIT_Y); // カメラ無しの初期値
    mProjectionMatrix = Matrix4::CreatePerspectiveFOV(Math::ToRadians(50.0f),
                                                      mGame->ScreenWidth, mGame->ScreenHeight,
                                                      25.0f, 300.0f);
    // カメラ作成
    mCamera = new Camera(mGame);
    mCamera->SetPosition(Vector3(0.0f, 5.0f, -15.0f));

    // ライティングパラメータ設定
    mAmbientLight = Vector3(0.35f, 0.35f, 0.35f);
    mDirLightDirection = Vector3(0.5f, -0.35f, 0.35f); // ReadySceneの方でも設定しているので注意！
    mDirLightDiffuseColor = Vector3(0.8f, 0.9f, 1.0f);
    mDirLightSpecColor = Vector3(0.8f, 0.8f, 0.8f);

    // 2DSprite用シェーダ作成
    m2DSpriteShader = new Shader(Shader::ShaderType::SPRITE);
    if (!m2DSpriteShader->Load(mGame))
    {
        return false;
    }

    // 2DSprite用頂点クラス作成（三角ポリゴン＊２）
    float vertices[] = {
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top left
             0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
             0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
            -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f  // bottom left
    };
    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };
    m2DSpriteVertexArray = new VertexArray(vertices, 4, indices, 6);

    // 2DSprite用ビュー行列取得
    m2DViewProjection = Matrix4::CreateSimpleViewProjection(mGame->ScreenWidth, mGame->ScreenHeight);

    return true;
}

void Renderer::Draw()
{
    // 背景色をクリア
    //glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearColor(19.0f/255.0f, 56.0f/255.0f, 111.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // アルファブレンド有効
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Zバッファ有効
    glEnable(GL_DEPTH_TEST);

    // メッシュ描画
    for (auto meshComp : mMeshComps)
    {
        meshComp->Draw();
    }

    // Zバッファ無効
    glDisable(GL_DEPTH_TEST);

    // スプライト描画
    m2DSpriteShader->SetActive();
    m2DSpriteShader->SetViewProjectionUniform(m2DViewProjection);
    m2DSpriteVertexArray->SetActive();
    for (auto sprite : mSpriteComps)
    {
        sprite->Draw(m2DSpriteShader);
    }

    // バックバッファとスワップ(ダブルバッファ)
    SDL_GL_SwapWindow(mWindow);
}

// 終了処理
void Renderer::ShutDown()
{
    // テクスチャを破棄
    for (auto i : mCachedTextures)
    {
        i.second->Unload();
        delete i.second;
    }
    mCachedTextures.clear();

    // メッシュを破棄
    for (auto i : mCachedMeshes)
    {
        i.second->Unload();
        delete i.second;
    }
    mCachedMeshes.clear();

    // シェーダを破棄
    for (auto i : mCachedShaders)
    {
        i.second->Unload();
        delete i.second;
    }
    mCachedShaders.clear();

    // 2DSprite用クラスを破棄
    m2DSpriteShader->Unload();
    delete m2DSpriteShader;
    delete m2DSpriteVertexArray;

    // SDL関連の変数を破棄
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

// スプライトコンポーネント追加・削除処理
void Renderer::AddSpriteComp(SpriteComponent* sprite)
{
    // 描画順にソートして追加
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter = mSpriteComps.begin();
    for (; iter != mSpriteComps.end(); ++iter)
    {
        if (myDrawOrder < (*iter)->GetDrawOrder())
        {
            break;
        }
    }
    mSpriteComps.insert(iter, sprite);
}
void Renderer::RemoveSpriteComp(SpriteComponent* sprite)
{
    auto iter = std::find(mSpriteComps.begin(), mSpriteComps.end(), sprite);
    mSpriteComps.erase(iter);
}

// メッシュコンポーネント追加・削除処理
void Renderer::AddMeshComp(class MeshComponent* mesh)
{
    mMeshComps.emplace_back(mesh);
}
void Renderer::RemoveMeshComp(class MeshComponent* mesh)
{
    auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
    mMeshComps.erase(iter);
}

// テクスチャロード処理
Texture* Renderer::GetTexture(const std::string &filePath)
{
    // キャッシュ済なら返却
    auto iter = mCachedTextures.find(filePath);
    if (iter != mCachedTextures.end()) return iter->second;

    Texture* texture = nullptr;
    texture = new Texture();
    if (texture->Load(filePath))
    {
        mCachedTextures.emplace(filePath, texture);
    }
    else
    {
        delete texture;
        texture = nullptr;
    }
    return texture;
}

// メッシュロード処理
Mesh* Renderer::GetMesh(const std::string &filePath)
{
    // キャッシュ済なら返却
    auto iter = mCachedMeshes.find(filePath);
    if (iter != mCachedMeshes.end()) return iter->second;

    Mesh* mesh = nullptr;
    mesh = new Mesh();
    if (mesh->Load(filePath, mGame))
    {
        mCachedMeshes.emplace(filePath, mesh);
    }
    else
    {
        delete mesh;
        mesh = nullptr;
    }
    return mesh;
}

// シェーダロード処理
Shader* Renderer::GetShader(const Shader::ShaderType type)
{
    // キャッシュ済なら返却
    auto iter = mCachedShaders.find(type);
    if (iter != mCachedShaders.end()) return iter->second;

    Shader* shader = nullptr;
    shader = new Shader(type);
    if (shader->Load(mGame))
    {
        // ViewProjection座標の設定
        shader->SetViewProjectionUniform(mProjectionMatrix * mViewMatrix);
        mCachedShaders.emplace(type, shader);
    }
    else
    {
        delete shader;
        shader = nullptr;
    }
    return shader;
}
