#ifndef MENUTEST_H
#define MENUTEST_H


#include "../Stage/Stage.h"
#include "RosalilaGraphics/RosalilaGraphics.h"
#include "RosalilaMenus/MenuContenedor.h"
#include "RosalilaMenus/MenuCharSelect.h"
#include "RosalilaSound/RosalilaSound.h"
#include "../STG.h"

#include <android/asset_manager.h>

#include <android/log.h>
#define APPNAME "MyApp"

class Menu
{
private:
    //Engines
    Sound* sonido;
    RosalilaGraphics* painter;
    Receiver* receiver;
    

    TiXmlDocument abrirXml(char* archivo);
    void dibujarMenu();
    int pos_stage,pos_ia_lvl;
    bool exit_signal,save_inputs_signal;
    MenuCharSelect* char_select;

    void iniciarJuego(std::string character_name,std::string stage_name,std::string dificulty);
public:
std::vector<Elemento*> elementos;
MenuContenedor*selectables_container;
    std::string music_path;
    RosalilaInputs *inputa,*inputb;
    Stage* stage;

    //Misc
    Image* loading_screen;

    Menu(){}
    Menu(RosalilaGraphics* painter,Receiver* receiver,Sound* sonido,char* archivo);
    void cargarDesdeXml(char*archivo,vector<std::string> chars,vector<std::string> stages);
    void loopMenu();
    std::string getStage();
    bool getExitSignal();
    bool getSaveRosalilaInputssSignal();
    void escribirRosalilaInputssXML(RosalilaInputs* ia,RosalilaInputs* ib);
    std::string getRosalilaInputsPressed();
    void llenarRosalilaInputssBotones();
    int toKeyCode(std::string str);
    void printLoadingScreen();
    void playMusic();
};

#endif
