#ifndef UI_HPP
#define UI_HPP

#include <wx/wx.h>
#include <wx/slider.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <regex>
#include <iostream>
#include "scene.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "cylinder.hpp"
#include "ray.hpp"
#include "rayhit.hpp"
#include "renderer.hpp"
#include "box.hpp"
#include "plane.hpp"
#include "colorRGB.hpp"
#include "material.hpp"

class MyFrame : public wxFrame {
public:
    Scene scene;
    Camera camera;
    Light light;
    Renderer renderer;

    MyFrame(const wxString& title);

private:
    wxPanel* panel;

    // Методы
    void InitScene();
    void OnUpdateImage(wxCommandEvent& event);
    void OnCameraMove(wxCommandEvent& event);
    void OnCameraRotate(wxCommandEvent& event);
    void OnSliderUpdate(wxCommandEvent& event);
    void OnColorChoice(wxCommandEvent& event);
    void OnRecursionSliderUpdate(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnEnterKey(wxKeyEvent& event);

    // Чекбоксы
    wxCheckBox* noiseCheckBox;
    wxCheckBox* smoothingCheckBox;

    // Поля для рекурсии
    wxSlider* recursionSlider;
    wxStaticText* recursionValue;

    // Поля для жидкости
    wxSlider* reflectivitySlider;
    wxStaticText* reflectivityValue;
    wxSlider* transparencySlider;
    wxStaticText* transparencyValue;
    wxSlider* refractiveSlider;
    wxStaticText* refractiveValue;
    wxChoice* colorChoice;

    // Поля для стержня
    wxSlider* rodReflectivitySlider;
    wxStaticText* rodReflectivityValue;
    wxChoice* rodColorChoice;

    // Поля для сосуда
    wxSlider* vesselReflectivitySlider;
    wxStaticText* vesselReflectivityValue;
    wxSlider* vesselTransparencySlider;
    wxStaticText* vesselTransparencyValue;
    wxSlider* vesselRefractiveSlider;
    wxStaticText* vesselRefractiveValue;
    wxChoice* vesselColorChoice;

    wxTextCtrl* xPos;
    wxTextCtrl* yPos;
    wxTextCtrl* zPos;

    // Поля для дополнительных параметров;
    wxButton* updateButton;

    // Кнопки для повора камеры
    wxButton* btnRotateForward;
    wxButton* btnRotateBackward;
    wxButton* btnRotateLeft;
    wxButton* btnRotateRight;

    // Кнопки для движения камеры
    wxButton* btnMoveForward;
    wxButton* btnMoveBackward;
    wxButton* btnMoveLeft;
    wxButton* btnMoveRight;
    wxButton* btnMoveUp;
    wxButton* btnMoveDown;
};

#endif // UI_HPP
