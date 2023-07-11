#pragma once
#include <format>
#include "../../../Events/Listener.hpp"
#include "../../../Events/Input/KeyEvent.hpp"
#include "../../../../Utils/Logger/Logger.hpp"
#include "../Module.hpp"
#include "../../../../SDK/SDK.hpp"
#include <Windows.h>

class MotionBlurListener : public Listener {

    Module* module;
    std::vector<ID2D1Bitmap*> previousFrames;
    const size_t maxFrames = 5; // Maximum number of frames to store

public:
    explicit MotionBlurListener(const char string[5], Module* module) {
        this->name = string;
        this->module = module;

    }

    void onRender(RenderEvent& event) override {

        if(module->settings.getSettingByName<bool>("enabled")->value) {


            if (previousFrames.size() >= maxFrames)
            {
                previousFrames[0]->Release();
                previousFrames.erase(previousFrames.begin());
            }

            ID2D1Bitmap* currentFrame = nullptr;

            if (SwapchainHook::queue != nullptr) FlarialGUI::CopyBitmap(SwapchainHook::D2D1Bitmaps[SwapchainHook::currentBitmap], &currentFrame);
            else FlarialGUI::CopyBitmap(SwapchainHook::D2D1Bitmap, &currentFrame);

            previousFrames.push_back(currentFrame);

            float alpha = 0.3f;
            for (ID2D1Bitmap* frame : previousFrames)
            {
                D2D::context->DrawBitmap(frame, D2D1::RectF(0.f, 0.f, MC::windowSize.x, MC::windowSize.y), alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
                alpha *= 0.7f;
            }
        }

    }
};
