#pragma once
/**
 * @file mascot_faces.h
 * @brief Mascot Faces - STUB (funcionalidade desabilitada, faces ASCII minimalistas)
 * @note A funcionalidade completa de mascotes foi desabilitada para economizar memória.
 */

#include <Arduino.h>

// Índices de face (para indexar FACE_ASCII array)
enum MascotFaceIndex {
    FACE_NONE = 0,
    FACE_HAPPY,
    FACE_SAD,
    FACE_ANGRY,
    FACE_BORED,
    FACE_SLEEP,
    FACE_SLEEP2,
    FACE_EXCITED,
    FACE_CURIOUS,
    FACE_CONFUSED,
    FACE_LOVE,
    FACE_COUNT
};

// Array de faces ASCII (indexado por MascotFaceIndex)
static const char* FACE_ASCII[] = {
    "",         // FACE_NONE
    "(•‿•)",    // FACE_HAPPY
    "(╥﹏╥)",   // FACE_SAD
    "(╬ಠ益ಠ)", // FACE_ANGRY
    "(-_-)",    // FACE_BORED
    "(-.-)Zzz", // FACE_SLEEP
    "( ᴗ_ᴗ)zZ", // FACE_SLEEP2
    "(ノ◕ヮ◕)ノ", // FACE_EXCITED
    "(・・?)",  // FACE_CURIOUS
    "(◎_◎;)",  // FACE_CONFUSED
    "(♥‿♥)",   // FACE_LOVE
};

// Tipos para compatibilidade
using MascotFaceType = MascotFaceIndex;

// Estrutura de face para compatibilidade
struct MascotFace {
    const char* name;
    MascotFaceType type;
    int width;
    int height;
    const uint8_t* data;
};

// Array vazio de faces (dados binários)
static const MascotFace mascotFaces[] = {};

// Funções vazias para evitar erros de compilação
inline const MascotFace* getMascotFace(MascotFaceType) { return nullptr; }
inline int getMascotFaceCount() { return 0; }
inline void drawMascotFace(MascotFaceType, int, int) {}
inline void drawMascotFaceByIndex(int, int, int) {}
inline const char* getFaceName(MascotFaceType t) { return FACE_ASCII[t]; }
