/**
 * @file FaultInjectionMenu.cpp
 * @brief Menu de Fault Injection (Voltage Glitching)
 * @author Lele Origin Team
 * @version 0.1 (Em Breve)
 */

#include "FaultInjectionMenu.h"
#include "core/display.h"
#include "core/utils.h"
#include <globals.h>

void FaultInjectionMenu::optionsMenu() {
    options.clear();

    // Placeholder - Feature em desenvolvimento
    displayWarning("FAULT INJECTION\n\nEm Breve!\n\nHardware:\nIRLZ44N MOSFET", true);
    delay(2000);

    // Menu placeholder para futuras opcoes
    options.push_back({"Voltage Glitch", [=]() {
        displayWarning("Em desenvolvimento\n\nUse IRLZ44N\nGPIO -> Gate\nDrain -> GND alvo\nSource -> VDD alvo", true);
    }});

    options.push_back({"Configurar GPIO", [=]() {
        displayInfo("GPIO padrao: 27\nPulse: 1-100 us\nDelay: 0-1000 us", true);
    }});

    options.push_back({"EMFI (Bobina)", [=]() {
        displayWarning("Em desenvolvimento\n\nRequer bobina + \ntransistor alta corrente", true);
    }});

    options.push_back({"Scripts Prontos", [=]() {
        displayInfo("Scripts para:\n- ESP32 flash keys\n- Smart locks\n- IoT devices", true);
    }});

    addOptionToMainMenu();
    loopOptions(options, MENU_TYPE_SUBMENU, "Fault Injection");
}

void FaultInjectionMenu::drawIconImg() {
    // Nao tem imagem de tema, usa icone desenhado
    drawIcon(1.0);
}

void FaultInjectionMenu::drawIcon(float scale) {
    clearIconArea();

    // Desenha icone de raio (lightning bolt) para fault injection
    int centerX = iconCenterX;
    int centerY = iconCenterY;
    int size = scale * 20;

    // Raio estilizado
    tft.fillTriangle(
        centerX - size/2, centerY - size,      // Topo esquerdo
        centerX + size/4, centerY - size/3,    // Meio direito
        centerX - size/4, centerY - size/3,    // Meio esquerdo
        leleConfig.priColor
    );

    tft.fillTriangle(
        centerX + size/4, centerY - size/3,    // Continua
        centerX - size/4, centerY + size/3,
        centerX + size/2, centerY + size,
        leleConfig.priColor
    );

    // Circulo de "target" ao redor
    tft.drawCircle(centerX, centerY, size * 1.5, leleConfig.priColor);
    tft.drawCircle(centerX, centerY, size * 1.8, leleConfig.secColor);
}
