
#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;

ncEditorData_t ncEditorData;

Vector2 anchor01 = { 900, 10 };
Texture2D cursorTexture;

//bool WindowBox000Active = true;

void InitEditor() {
    GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

    Image i = LoadImage("resources/R.png");
    cursorTexture = LoadTextureFromImage(i);
    UnloadImage(i);
    HideCursor();

    ncEditorData.anchor01 = (Vector2){ 808, 24 };
    ncEditorData.anchor02 = (Vector2){ 816, 72 };
    ncEditorData.anchor03 = (Vector2){ 816, 264 };

    ncEditorData.EditorBoxActive = true;
    ncEditorData.BodyTypeEditMode = false;
    ncEditorData.DampingValue = 0.0f;
    ncEditorData.GravitationValue = 0.0f;
    ncEditorData.BodyTypeActive = 0;
    ncEditorData.GravityScaleValue = 1.0f;
    ncEditorData.MassValue = 2.0f;
    ncEditorData.StiffnessValue = 10.0f;
    ncEditorData.GravityValue = 0.0f;

    editorRect = (Rectangle){ ncEditorData.anchor01.x + 0, ncEditorData.anchor01.y + 0, 304, 616 };
}

void UpdateEditor(Vector2 position) {
    if (IsKeyPressed(KEY_TAB)) ncEditorData.EditorBoxActive = !ncEditorData.EditorBoxActive;

    ncEditorIntersect = ncEditorData.EditorBoxActive && CheckCollisionPointRec(position, editorRect);
}
//232
void DrawEditor(Vector2 position) {
    if (ncEditorData.BodyTypeEditMode) GuiLock();

    if (ncEditorData.EditorBoxActive) {
        ncEditorData.EditorBoxActive = !GuiWindowBox((Rectangle) { ncEditorData.anchor01.x + -16, ncEditorData.anchor01.y + 0, 288, 656 }, "Editor");
        GuiGroupBox((Rectangle) { ncEditorData.anchor02.x + 0, ncEditorData.anchor02.y + 0, 242, 168 }, "Body");
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 80, ncEditorData.anchor02.y + 64, 120, 16 }, "Mass", TextFormat("% 0.2f", ncEditorData.MassValue), & ncEditorData.MassValue, 0.5, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 80, ncEditorData.anchor02.y + 88, 120, 16 }, "Damping", TextFormat("% 0.2f", ncEditorData.DampingValue), & ncEditorData.DampingValue, 0, 10);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 80, ncEditorData.anchor02.y + 112, 120, 16 }, "Gravity Scale", TextFormat("% 0.2f", ncEditorData.GravityScaleValue), & ncEditorData.GravityScaleValue, 0, 20);
        GuiSliderBar((Rectangle) { ncEditorData.anchor02.x + 80, ncEditorData.anchor02.y + 136, 120, 16 }, "Stiffness (k)", TextFormat("% 0.2f", ncEditorData.StiffnessValue), & ncEditorData.StiffnessValue, 0, 10);
        GuiGroupBox((Rectangle) { ncEditorData.anchor03.x + 0, ncEditorData.anchor03.y + 0, 242, 96 }, "World");
        GuiSlider((Rectangle) { ncEditorData.anchor03.x + 80, ncEditorData.anchor03.y + 16, 120, 16 }, "Gravity", TextFormat("% 0.2f", ncEditorData.GravityValue), & ncEditorData.GravityValue, -10, 10);
        GuiSlider((Rectangle) { ncEditorData.anchor03.x + 80, ncEditorData.anchor03.y + 36, 120, 16 }, "Gravitation", TextFormat("% 0.2f", ncEditorData.GravitationValue), & ncEditorData.GravitationValue, -10, 10);
        if (GuiDropdownBox((Rectangle) { ncEditorData.anchor02.x + 64, ncEditorData.anchor02.y + 24, 120, 24 }, "Dynamic;Kinematic;Static", & ncEditorData.BodyTypeActive, ncEditorData.BodyTypeEditMode)) ncEditorData.BodyTypeEditMode = !ncEditorData.BodyTypeEditMode;
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, GREEN);

    GuiUnlock();
}

ncBody* GetBodyIntersect(ncBody* bodies, Vector2 position) {
    for (ncBody* body = bodies; body; body = body->next) {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f))) {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(ncBody* body, Vector2 position) {
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}
