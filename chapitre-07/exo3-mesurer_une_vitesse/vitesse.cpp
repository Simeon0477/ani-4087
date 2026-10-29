#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"

#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkMouseEvent.h"

#include "NKLogger/NkLog.h"

#include "NKMath/NkQuat.h"

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

    // Sensibilite de la souris : radian par unite de mouvement brut.
    const float32 kSensibilite = 0.0022f;
    const float32 kRadVersDeg = 57.29577951f;

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

    // Vitesse angulaire entre deux poses horodatees (rad/s, vecteur : axe * vitesse).
    NkVec3f VitesseAngulaire(const NkQuatf &from, const NkQuatf &to, float32 dtSeconds) {
        if (dtSeconds <= 0.f) {
            return NkVec3f(0.f, 0.f, 0.f);
        }
        NkQuatf delta = (to * from.Conjugate()).Normalized();
        // Les deux hemispheres du quaternion codent la meme rotation ; on
        // force le chemin court, sinon un delta minuscule peut se lire
        // comme un tour presque complet dans l'autre sens.
        if (delta.w < 0.f) {
            delta = NkQuatf(-delta.x, -delta.y, -delta.z, -delta.w);
        }
        const float32 angleRad = delta.Angle().Rad();
        if (angleRad <= 1e-6f) {
            return NkVec3f(0.f, 0.f, 0.f);
        }
        return delta.Axis() * (angleRad / dtSeconds);
    }

} // namespace

int nkmain(const NkEntryState &state) {

    // Tour programme : MASALLE_TOUR = vitesse en degres par seconde (0 = souris).
    const char *tourTexte = std::getenv("MASALLE_TOUR");
    
    const float64 tourDegS = tourTexte ? std::atof(tourTexte) : 0.0;
    const bool modeTour = (tourDegS != 0.0);

    // Premiere image imprimee (par defaut 30, les premieres paient le demarrage).
    int imageDebut = 30;
    if (const char *d = std::getenv("MASALLE_DEBUT")) {
        const int v = std::atoi(d);
        if (v > 0) imageDebut = v;
    }
    const int kLignes = 20;

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

    int imageMax = 0;
    if (const char *sortie = std::getenv("MASALLE_EXIT")) {
        imageMax = std::atoi(sortie);
    }

    // Etat de la tete.
    float32 lacetRad = 0.f;
    float32 tangageRad = 0.f;
    float32 cumulDx = 0.f;   // accumulateur des mouvements bruts de souris
    float32 cumulDy = 0.f;

    // Pose precedente (orientation + instant en secondes).
    NkQuatf orientationPrec(0.f, 0.f, 0.f, 1.f);
    float64 instantPrecS = 0.0;
    bool aPrecedent = false;

    int numeroImage = 0;
    int lignesImprimees = 0;
    bool serieAnnoncee = false;

    while (running) {
        // Instant de cette image, en secondes depuis le lancement.
        const float64 maintenantS = static_cast<float64>(
            static_cast<long long>(NkChrono::Now().nanoseconds) - t0) * 1e-9;

        // 1) Pompe d'evenements : on ACCUMULE les mouvements bruts de souris.
        NkEvent *event;
        while (eventSystem.PollEvent(event)) {
            if (event->Is<NkWindowCloseEvent>()) {
                running = false;
            }
            if (auto *m = event->As<NkMouseRawEvent>()) {
                cumulDx += static_cast<float32>(m->GetDeltaX());
                cumulDy += static_cast<float32>(m->GetDeltaY());
            }
        }
        if (!running) break;

        ++numeroImage;
        if (imageMax > 0 && numeroImage > imageMax) {
            break;
        }

        // 2) Une fois par image : on applique l'accumulateur, puis on le vide.
        if (modeTour) {
            // Le lacet suit l'horloge, pas la souris.
            lacetRad = static_cast<float32>(tourDegS * maintenantS * 0.017453292519943295);
        } else {
            lacetRad -= cumulDx * kSensibilite;
            tangageRad -= cumulDy * kSensibilite;
            if (tangageRad > 1.5f) tangageRad = 1.5f;
            if (tangageRad < -1.5f) tangageRad = -1.5f;
        }
        cumulDx = 0.f;
        cumulDy = 0.f;

        // 3) Orientation : deux matrices, puis conversion en quaternion.
        const NkMat4f rotation = NkMat4f::RotationY(NkAngle::FromRad(lacetRad)) *
                                 NkMat4f::RotationX(NkAngle::FromRad(tangageRad));
        const NkQuatf orientation = NkQuatf(rotation).Normalized();

        // 4) Vitesse angulaire entre la pose precedente et celle-ci.
        if (aPrecedent) {
            const float32 dtS = static_cast<float32>(maintenantS - instantPrecS);
            const NkVec3f omega = VitesseAngulaire(orientationPrec, orientation, dtS);

            if (numeroImage >= imageDebut && lignesImprimees < kLignes) {
                if (!serieAnnoncee) {
                    Dire(modeTour ? "serie programme" : "serie souris");
                    serieAnnoncee = true;
                }
                char ligne[200];
                std::snprintf(ligne, sizeof(ligne),
                              "image %d : dt = %.3f ms, vitesse = (%.2f, %.2f, %.2f) deg/s",
                              lignesImprimees + 1, dtS * 1000.f,
                              omega.x * kRadVersDeg, omega.y * kRadVersDeg,
                              omega.z * kRadVersDeg);
                Dire(ligne);
                ++lignesImprimees;
            }
        }
        orientationPrec = orientation;
        instantPrecS = maintenantS;
        aPrecedent = true;

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
            // La camera suit l'orientation de la tete.
            cd.target = cd.position + orientation * NkVec3f(0.f, 0.f, -1.f);
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

    NkRenderer::Destroy(renderer);
    NkRenderer::Destroy(rEcran);
    NkDeviceFactory::Destroy(device);
    return 0;
}