#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

#include "NKEvent/NkEventSystem.h"

#include "NKLogger/NkLog.h"

#include "NKTime/NkClock.h"
#include "NKTime/NkChrono.h"

#include "NKRHI/Core/NkDeviceFactory.h"
#include "NKRHI/Core/NkGraphicsApi.h"

#include "NKRenderer/NkRenderer.h"
#include "NKRenderer/Core/NkCamera.h"
#include "NKRenderer/Core/NkRenderGraph.h"
#include "NKRenderer/Core/NkTextureLibrary.h"
#include "NKRenderer/Materials/NkMaterialCollection.h"
#include "NKRenderer/Mesh/NkMeshSystem.h"
#include "NKRenderer/Tools/Offscreen/NkOffscreenTarget.h"
#include "NKRenderer/Tools/Render2D/NkRender2D.h"
#include "NKRenderer/Tools/Render3D/NkRender3D.h"

#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace nkentseu;
using namespace nkentseu::renderer;

namespace {

    const float32 kPiece = 4.00f;
    const float32 kPlafond = 2.50f;
    const float32 kMur = 0.10f;
    const float32 kPorteL = 0.90f;
    const float32 kPorteH = 2.00f;
    const float32 kFenL = 1.20f;
    const float32 kFenH = 1.00f;
    const float32 kFenY = 1.40f;
    const float32 kTableL = 1.20f;
    const float32 kTableP = 0.80f;
    const float32 kTableH = 0.75f;
    const float32 kYeux = 1.70f;
    const float32 kDemi = kPiece * 0.5f;

    void Pave(NkRender3D *r3d, NkMeshSystem *meshes, const NkVec3f &centre,
              const NkVec3f &taille, const NkVec3f &teinte, float32 rugosite = 1.f) {
        NkDrawCall3D dc;
        dc.mesh = meshes->GetCube();
        dc.transform = NkMat4f::Translate(centre) * NkMat4f::Scale(taille);
        dc.aabb = { { centre.x - taille.x * 0.5f, centre.y - taille.y * 0.5f,
                      centre.z - taille.z * 0.5f },
                    { centre.x + taille.x * 0.5f, centre.y + taille.y * 0.5f,
                      centre.z + taille.z * 0.5f } };
        dc.tint = teinte;
        dc.metallic = 0.f;
        dc.roughness = rugosite;
        r3d->Submit(dc);
    }

    void SoumettreLaSalle(NkRender3D *r3d, NkMeshSystem *meshes) {
        const NkVec3f grisMur = { 0.72f, 0.70f, 0.66f };
        const NkVec3f grisSol = { 0.38f, 0.36f, 0.34f };
        const NkVec3f bois = { 0.55f, 0.38f, 0.22f };
        const NkVec3f vitre = { 0.75f, 0.85f, 0.92f };

        {
            NkDrawCall3D dc;
            dc.mesh = meshes->GetPlane();
            dc.transform = NkMat4f::Scale({ kPiece, 1.f, kPiece });
            dc.aabb = { { -kDemi, 0.f, -kDemi }, { kDemi, 0.f, kDemi } };
            dc.castShadow = false;
            dc.tint = grisSol;
            dc.metallic = 0.f;
            dc.roughness = 1.f;
            r3d->Submit(dc);
        }

        const float32 yMur = kPlafond * 0.5f;
        const float32 bord = kDemi + kMur * 0.5f;

        Pave(r3d, meshes, { 0.f, yMur, -bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { 0.f, yMur, bord }, { kPiece, kPlafond, kMur }, grisMur);
        Pave(r3d, meshes, { -bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);
        Pave(r3d, meshes, { bord, yMur, 0.f }, { kMur, kPlafond, kPiece }, grisMur);

        Pave(r3d, meshes, { 0.f, kPlafond + kMur * 0.5f, 0.f },
             { kPiece, kMur, kPiece }, grisMur);

        Pave(r3d, meshes, { -0.70f, kPorteH * 0.5f, -kDemi + 0.02f },
             { kPorteL, kPorteH, 0.04f }, bois, 0.6f);

        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, -0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);
        Pave(r3d, meshes, { -kDemi + 0.02f, kFenY, 0.90f },
             { 0.04f, kFenH, kFenL }, vitre, 0.15f);

        const float32 tx = 0.60f, tz = 0.70f;
        const float32 ep = 0.05f;
        Pave(r3d, meshes, { tx, kTableH - ep * 0.5f, tz },
             { kTableL, ep, kTableP }, bois, 0.5f);

        const float32 pied = 0.06f;
        const float32 hp = kTableH - ep;
        for (int i = 0; i < 4; ++i) {
            const float32 dx = ((i & 1) ? 1.f : -1.f) * (kTableL * 0.5f - pied);
            const float32 dz = ((i & 2) ? 1.f : -1.f) * (kTableP * 0.5f - pied);
            Pave(r3d, meshes, { tx + dx, hp * 0.5f, tz + dz },
                 { pied, hp, pied }, bois, 0.6f);
        }

        Pave(r3d, meshes, { -1.10f, 0.50f, 1.20f }, { 1.f, 1.f, 1.f },
             { 0.85f, 0.80f, 0.30f }, 0.8f);
    }

    void Dire(const char *ligne) {
        std::printf("%s\n", ligne);
        std::fflush(stdout);
        logger.Info("{0}", ligne);
    }

} // namespace

int nkmain(const NkEntryState &state) {

    // La cadence se lit dans MASALLE_HZ, 72 par defaut, comme le simulateur du moteur.
    const char *hzTexte = std::getenv("MASALLE_HZ");
    const float64 hzLu = hzTexte ? std::atof(hzTexte) : 0.0;
    const float64 hz = (hzLu > 1.0) ? hzLu : 72.0;

    // La periode d'affichage, en nanosecondes : 1e9 / hz.
    const float64 periodeNs = 1e9 / hz;
    const float64 periodeMs = periodeNs / 1.0e6;

    // L'origine des instants : tous sont comptes depuis le lancement.
    const long long t0 = static_cast<long long>(NkChrono::Now().nanoseconds);

    NkWindowConfig cfg;
    cfg.title = "Renderer And RHI";
    cfg.width = 1280;
    cfg.height = 720;

    NkWindow window;

    if (!window.Create(cfg)) {
        logger.Error("La fenetre n'a pas ete creee");
        return -1;
    }

    NkDeviceInitInfo devInit{};
    devInit.surface = window.GetSurfaceDesc();
    devInit.width = window.GetSize().x;
    devInit.height = window.GetSize().y;

    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInit);
    if (device == nullptr) {
        logger.Error("Echec de creation du device");
        return -2;
    }

    logger.Info("[Render] API graphique retenue : {0}, surface de {1}x{2}", NkGraphicsApiName(devInit.api), devInit.width, devInit.height);

    NkRendererConfig cfgEcran = NkRendererConfig::For2D(devInit.api, devInit.width, devInit.height);
    NkRenderer *rEcran = NkRenderer::Create(device, cfgEcran);

    if (rEcran == nullptr || !rEcran->Initialize()) {
        logger.Error("Echec de creation du renderer");
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    NkOffscreenDesc od;
    od.width = devInit.width;
    od.height = devInit.height;
    od.hasDepth = true;
    od.hdr = false;
    od.colorFmt = NkGPUFormat::NK_RGBA8_UNORM;
    od.readable = true;
    od.readback = true;
    od.name = "Render_Cible";

    NkOffscreenTarget *cible = rEcran->CreateOffscreen(od);
    if (cible == nullptr) {
        logger.Error("[Render] cible hors ecran refusee");
        NkRenderer::Destroy(rEcran);
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    NkRendererConfig cfgScene = NkRendererConfig::ForGame(devInit.api, devInit.width, devInit.height);
    cfgScene.Disable(NK_SS_RENDER2D);
    cfgScene.Disable(NK_SS_TEXT);
    cfgScene.Disable(NK_SS_OVERLAY);
    cfgScene.Enable(NK_SS_OFFSCREEN);

    NkRenderer *renderer = NkRenderer::Create(device, cfgScene);
    if (renderer == nullptr || !renderer->Initialize()) {
        logger.Error("[Render] le renderer de la scene n'a pas pu s'initialiser");
        NkRenderer::Destroy(rEcran);
        NkDeviceFactory::Destroy(device);
        return 1;
    }

    renderer->SetFinalColorTarget(rEcran->GetTextures()->GetRHIHandle(cible->GetColorResult()));

    auto &eventSystem = NkEvents();
    bool running = true;

    NkClock horloge;

    const int kEcartees = 30;   // images de demarrage ecartees
    const int kVoulues = 600;   // ecarts reel - predit a moyenner
    const int kLignes = 20;     // lignes d'instants a imprimer

    std::vector<double> ecarts;
    ecarts.reserve(kVoulues);

    float64 preditPrecedentNs = 0.0;
    int numeroImage = 0;

    int imageMax = 0;
    if (const char *sortie = std::getenv("MASALLE_EXIT")) {
        imageMax = std::atoi(sortie);
    }

    while (running) {
        // Debut reel de cette image, en nanosecondes depuis le lancement.
        // La soustraction se fait en entier, puis passe en float64.
        const float64 maintenantNs = static_cast<float64>(
            static_cast<long long>(NkChrono::Now().nanoseconds) - t0);

        // reel - predit : debut REEL de cette image moins l'instant PREDIT
        // a l'image d'avant.
        if (numeroImage > kEcartees && (int)ecarts.size() < kVoulues) {
            ecarts.push_back((maintenantNs - preditPrecedentNs) / 1.0e6);
        }

        // Comme le simulateur : predit = maintenant + periode.
        const float64 preditNs = maintenantNs + periodeNs;

        if (numeroImage > kEcartees && numeroImage <= kEcartees + kLignes) {
            char ligne[160];
            std::snprintf(ligne, sizeof(ligne),
                          "maintenant = %.3f ms, predit = %.3f ms, ecart = %.3f ms",
                          maintenantNs / 1.0e6, preditNs / 1.0e6,
                          (preditNs - maintenantNs) / 1.0e6);
            Dire(ligne);
        }

        preditPrecedentNs = preditNs;
        ++numeroImage;

        if (imageMax > 0 && numeroImage > imageMax) {
            break;
        }

        NkEvent *event;
        while (eventSystem.PollEvent(event)) {
            if (event->Is<NkWindowCloseEvent>()) {
                running = false;
            }
        }

        if (!running) break;

        const NkClock::NkTime &temps = horloge.Tick();

        if (rEcran->BeginFrame()) {
            NkICommandBuffer *cmd = rEcran->GetCmd();
            NkRender3D *r3d = renderer->GetRender3D();

            renderer->FlushGraphRebuilds();
            r3d->ResetFrame();
            if (auto *mc = renderer->GetMaterialCollection()) {
                mc->Upload();
            }

            NkCamera3DData cd;
            cd.position = { 0.30f, kYeux, 1.20f };
            cd.target = { -0.7f, 1.10f, -kDemi };
            cd.up = { 0.f, 1.f, 0.f };
            cd.fovY = 70.f;
            cd.aspect = (float32)devInit.width / (float32)devInit.height;
            cd.nearPlane = 0.05f;
            cd.farPlane = 100.f;

            NkSceneContext sctx;
            sctx.camera = NkCamera3D(cd);
            sctx.time = temps.total;

            NkLightDesc soleil;
            soleil.type = NkLightType::NK_DIRECTIONAL;
            soleil.direction = { -0.5f, -1.f, -0.35f };
            soleil.color = { 1.f, 0.96f, 0.88f };
            soleil.intensity = 3.f;
            soleil.castShadow = false;

            sctx.lights.PushBack(soleil);

            r3d->SetIBLStrength(0.35f);
            r3d->BeginScene(sctx);

            SoumettreLaSalle(r3d, renderer->GetMeshSystem());

            if (auto *graph = renderer->GetRenderGraph()) {
                graph->Execute(cmd);
            }

            if (auto *r2d = rEcran->GetRender2D()) {
                r2d->Begin(cmd, devInit.width, devInit.height);
                r2d->DrawImage(cible->GetColorResult(), { 0.f, 0.f, (float32)devInit.width, (float32)devInit.height });
                r2d->End();
            }

            rEcran->Present();
            rEcran->EndFrame();
        } else {
            logger.Error("BeginFrame a refuse l'image");
        }
    }

    if (!ecarts.empty()) {
        double somme = 0.0;
        for (double v : ecarts) somme += v;
        const double moyenne = somme / ecarts.size();

        char ligne[160];
        std::snprintf(ligne, sizeof(ligne),
                      "hz = %.0f, periode = %.3f ms, reel - predit = %.3f ms",
                      hz, periodeMs, moyenne);
        Dire(ligne);

        std::snprintf(ligne, sizeof(ligne), "intervalles mesures : %d", (int)ecarts.size());
        Dire(ligne);
    }

    NkRenderer::Destroy(renderer);
    NkRenderer::Destroy(rEcran);
    NkDeviceFactory::Destroy(device);
    return 0;
}