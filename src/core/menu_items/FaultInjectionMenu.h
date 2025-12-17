/**
 * @file FaultInjectionMenu.h
 * @brief Menu de Fault Injection (Injecao de Falhas)
 * @author Lele Origin Team
 * @version 0.1 (Em Breve)
 *
 * Hardware necessario:
 * - MOSFET IRLZ44N
 * - Resistor 10-100 Ohm
 * - Fios/Protoboard
 */

#ifndef __FAULT_INJECTION_MENU_H__
#define __FAULT_INJECTION_MENU_H__

#include <MenuItemInterface.h>

class FaultInjectionMenu : public MenuItemInterface {
public:
    FaultInjectionMenu() : MenuItemInterface("Glitcher") {}

    void optionsMenu(void);
    void drawIcon(float scale);
    void drawIconImg();
    bool getTheme() { return false; }  // Usar icone desenhado
};

#endif
