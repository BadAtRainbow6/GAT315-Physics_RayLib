
#pragma once
#include "raylib.h"

typedef struct ncEditorData {
    Vector2 anchor01;
    Vector2 anchor02;
    Vector2 anchor03;

    bool EditorBoxActive;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float MassValue;
    float DampingValue;
    float GravityScaleValue;
    float GravitationValue;
    float StiffnessValue;
    float GravityValue;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();

struct ncBody* GetBodyIntersect(struct ncBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct ncBody* body, Vector2 position);
