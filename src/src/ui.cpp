#include "ui.hpp"

#define WIDTH 1024
#define HEIGHT 720

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(950, 370)),
      light(vec3(-3.0, 7.0, -3.0)) {
    InitScene();
   
    panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Основной sizer для двух строк
    wxBoxSizer* rowSizer1 = new wxBoxSizer(wxHORIZONTAL);  // Первая строка
    wxBoxSizer* rowSizer2 = new wxBoxSizer(wxHORIZONTAL);  // Вторая строка

    // Секция 1.0 Параметры жидкости
    wxStaticBox* liquidBox = new wxStaticBox(panel, wxID_ANY, "Параметры жидкости");
    wxStaticBoxSizer* liquidSizer = new wxStaticBoxSizer(liquidBox, wxVERTICAL);

    // Ползунок для отражаемости жидкости
    reflectivitySlider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
    reflectivitySlider->SetValue((scene.Shapes[0]->material.reflectivity) * 100);
    reflectivityValue = new wxStaticText(panel, wxID_ANY, "0.50");
    reflectivityValue->SetLabel(wxString::Format("%.2f", scene.Shapes[0]->material.reflectivity));

    // Ползунок для прозрачности жидкости
    transparencySlider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
    transparencySlider->SetValue((scene.Shapes[0]->material.transparency) * 100);
    transparencyValue = new wxStaticText(panel, wxID_ANY, "0.50");
    transparencyValue->SetLabel(wxString::Format("%.2f", scene.Shapes[0]->material.transparency));

    // Ползунок для коэффициента преломления
    refractiveSlider = new wxSlider(panel, wxID_ANY, 10, 10, 20);
    refractiveSlider->SetValue((scene.Shapes[0]->material.refractiveIndex) * 10);
    refractiveValue = new wxStaticText(panel, wxID_ANY, "1.00");
    refractiveValue->SetLabel(wxString::Format("%.2f", scene.Shapes[0]->material.refractiveIndex));

    // Выпадающий список для выбора цвета
    colorChoice = new wxChoice(panel, wxID_ANY);
    colorChoice->Append("Синий");
    colorChoice->Append("Серый");
    colorChoice->Append("Зеленый");
    colorChoice->Append("Красный");

    // Секция 1.1.0 Позиция света и Дополнительные параметры
    wxBoxSizer* lightAndOptionsSizer = new wxBoxSizer(wxVERTICAL);

    // Секция 1.1.0 Позиция света
    wxStaticBox* lightBox = new wxStaticBox(panel, wxID_ANY, "Параметры источника света");
    wxStaticBoxSizer* lightSizer = new wxStaticBoxSizer(lightBox, wxVERTICAL);

    wxBoxSizer* positionSizer = new wxBoxSizer(wxHORIZONTAL);
    xPos = new wxTextCtrl(panel, wxID_ANY, wxString::Format("%.2f", scene.light.pos.x));
    yPos = new wxTextCtrl(panel, wxID_ANY, wxString::Format("%.2f", scene.light.pos.y));
    zPos = new wxTextCtrl(panel, wxID_ANY, wxString::Format("%.2f", scene.light.pos.z));
    positionSizer->Add(xPos, 0, wxALL, 5);
    positionSizer->Add(yPos, 0, wxALL, 5);
    positionSizer->Add(zPos, 0, wxALL, 5);

    // Секция 1.1.1 Дополнительные параметры
    wxStaticBox* optionsBox = new wxStaticBox(panel, wxID_ANY, "Дополнительные параметры");
    wxStaticBoxSizer* optionsSizer = new wxStaticBoxSizer(optionsBox, wxVERTICAL);

    // Чекбоксы для шума и сглаживания
    noiseCheckBox = new wxCheckBox(panel, wxID_ANY, "Шум");
    smoothingCheckBox = new wxCheckBox(panel, wxID_ANY, "Сглаживание");
    optionsSizer->Add(noiseCheckBox, 0, wxALL, 5);
    optionsSizer->Add(smoothingCheckBox, 0, wxALL, 5);

    // Ползунок для глубины рекурсии
    optionsSizer->Add(new wxStaticText(panel, wxID_ANY, "Глубина рекурсии:"), 0, wxALL, 5);
    recursionSlider = new wxSlider(panel, wxID_ANY, 4, 0, 8);
    recursionValue = new wxStaticText(panel, wxID_ANY, "4");
    recursionSlider->SetValue((renderer.MAX_BOUNCES));
    recursionValue->SetLabel(wxString::Format("%d", renderer.MAX_BOUNCES));
    wxBoxSizer* recursionSizer = new wxBoxSizer(wxHORIZONTAL);
    recursionSizer->Add(recursionSlider, 1, wxALL | wxEXPAND, 5);
    recursionSizer->Add(recursionValue, 0, wxALL, 5);
    optionsSizer->Add(recursionSizer, 0, wxALL | wxEXPAND, 5);

    // Кнопка обновления изображения
    updateButton = new wxButton(panel, wxID_ANY, "Обновить изображение");
    optionsSizer->Add(updateButton, 0, wxALL | wxEXPAND, 5);

    // Секция 2.0 Параметры стержня
    wxStaticBox* rodBox = new wxStaticBox(panel, wxID_ANY, "Параметры стержня");
    wxStaticBoxSizer* rodSizer = new wxStaticBoxSizer(rodBox, wxVERTICAL);

    // Ползунок для отражаемости стержня
    rodSizer->Add(new wxStaticText(panel, wxID_ANY, "Отражаемость:"), 0, wxALL, 5);
    rodReflectivitySlider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
    rodReflectivityValue = new wxStaticText(panel, wxID_ANY, "0.50");
    rodReflectivitySlider->SetValue((scene.Shapes[1]->material.reflectivity) * 100);
    rodReflectivityValue->SetLabel(wxString::Format("%.2f", scene.Shapes[1]->material.reflectivity));
    wxBoxSizer* rodReflectivitySizer = new wxBoxSizer(wxHORIZONTAL);
    rodReflectivitySizer->Add(rodReflectivitySlider, 1, wxALL | wxEXPAND, 5);
    rodReflectivitySizer->Add(rodReflectivityValue, 0, wxALL, 5);
    rodSizer->Add(rodReflectivitySizer, 0, wxALL | wxEXPAND, 5);

    rodSizer->Add(new wxStaticText(panel, wxID_ANY, "Цвет:"), 0, wxALL, 5);
    rodColorChoice = new wxChoice(panel, wxID_ANY);
    rodColorChoice->Append("Зеленый");
    rodColorChoice->Append("Синий");
    rodColorChoice->Append("Серый");
    rodColorChoice->Append("Красный");
    rodSizer->Add(rodColorChoice, 0, wxALL | wxEXPAND, 5);

    //rowSizer1->Add(rodSizer, 1, wxALL | wxEXPAND, 5);

    // Секция 2.1 Параметры сосуда
    wxStaticBox* vesselBox = new wxStaticBox(panel, wxID_ANY, "Параметры сосуда");

    // Ползунок для отражаемости сосуда
    vesselReflectivitySlider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
    vesselReflectivityValue = new wxStaticText(panel, wxID_ANY, "0.50");
    vesselReflectivitySlider->SetValue((scene.Shapes[2]->material.reflectivity) * 100);
    vesselReflectivityValue->SetLabel(wxString::Format("%.2f", scene.Shapes[2]->material.reflectivity));

    // Ползунок для прозрачности сосуда
    vesselTransparencySlider = new wxSlider(panel, wxID_ANY, 50, 0, 100);
    vesselTransparencyValue = new wxStaticText(panel, wxID_ANY, "0.50");
    vesselTransparencySlider->SetValue((scene.Shapes[2]->material.transparency) *100);
    vesselTransparencyValue->SetLabel(wxString::Format("%.2f", scene.Shapes[2]->material.transparency));

    // Ползунок для коэффициента преломления сосуда
    vesselRefractiveSlider = new wxSlider(panel, wxID_ANY, 10, 10, 20);
    vesselRefractiveValue = new wxStaticText(panel, wxID_ANY, "1.00");
    vesselRefractiveSlider->SetValue((scene.Shapes[2]->material.refractiveIndex) *10);
    vesselRefractiveValue->SetLabel(wxString::Format("%.2f", scene.Shapes[2]->material.refractiveIndex));

    // Цвет сосуда
    vesselColorChoice = new wxChoice(panel, wxID_ANY);
    vesselColorChoice->Append("Серый");
    vesselColorChoice->Append("Синий");
    vesselColorChoice->Append("Зеленый");
    vesselColorChoice->Append("Красный");

    wxBoxSizer* vesselLiquidSizer = new wxBoxSizer(wxHORIZONTAL);

    liquidSizer->Add(new wxStaticText(panel, wxID_ANY, "Отражаемость:"), 0, wxALL, 5);
    wxBoxSizer* reflectivitySizer = new wxBoxSizer(wxHORIZONTAL);
    reflectivitySizer->Add(reflectivitySlider, 1, wxALL | wxEXPAND, 5);
    reflectivitySizer->Add(reflectivityValue, 0, wxALL, 5);
    liquidSizer->Add(reflectivitySizer, 0, wxALL | wxEXPAND, 5);

    liquidSizer->Add(new wxStaticText(panel, wxID_ANY, "Прозрачность:"), 0, wxALL, 5);
    wxBoxSizer* transparencySizer = new wxBoxSizer(wxHORIZONTAL);
    transparencySizer->Add(transparencySlider, 1, wxALL | wxEXPAND, 5);
    transparencySizer->Add(transparencyValue, 0, wxALL, 5);
    liquidSizer->Add(transparencySizer, 0, wxALL | wxEXPAND, 5);

    liquidSizer->Add(new wxStaticText(panel, wxID_ANY, "Коэффициент преломления:"), 0, wxALL, 5);
    wxBoxSizer* refractiveSizer = new wxBoxSizer(wxHORIZONTAL);
    refractiveSizer->Add(refractiveSlider, 1, wxALL | wxEXPAND, 5);
    refractiveSizer->Add(refractiveValue, 0, wxALL, 5);
    liquidSizer->Add(refractiveSizer, 0, wxALL | wxEXPAND, 5);

    liquidSizer->Add(new wxStaticText(panel, wxID_ANY, "Цвет:"), 0, wxALL, 5);
    liquidSizer->Add(colorChoice, 0, wxALL | wxEXPAND, 5);

    wxStaticBoxSizer* vesselSizer = new wxStaticBoxSizer(vesselBox, wxVERTICAL);

    vesselSizer->Add(new wxStaticText(panel, wxID_ANY, "Отражаемость:"), 0, wxALL, 5);
    wxBoxSizer* vesselReflectivitySizer = new wxBoxSizer(wxHORIZONTAL);
    vesselReflectivitySizer->Add(vesselReflectivitySlider, 1, wxALL | wxEXPAND, 5);
    vesselReflectivitySizer->Add(vesselReflectivityValue, 0, wxALL, 5);
    vesselSizer->Add(vesselReflectivitySizer, 0, wxALL | wxEXPAND, 5);

    vesselSizer->Add(new wxStaticText(panel, wxID_ANY, "Прозрачность:"), 0, wxALL, 5);
    wxBoxSizer* vesselTransparencySizer = new wxBoxSizer(wxHORIZONTAL);
    vesselTransparencySizer->Add(vesselTransparencySlider, 1, wxALL | wxEXPAND, 5);
    vesselTransparencySizer->Add(vesselTransparencyValue, 0, wxALL, 5);
    vesselSizer->Add(vesselTransparencySizer, 0, wxALL | wxEXPAND, 5);

    vesselSizer->Add(new wxStaticText(panel, wxID_ANY, "Коэффициент преломления:"), 0, wxALL, 5);
    wxBoxSizer* vesselRefractiveSizer = new wxBoxSizer(wxHORIZONTAL);
    vesselRefractiveSizer->Add(vesselRefractiveSlider, 1, wxALL | wxEXPAND, 5);
    vesselRefractiveSizer->Add(vesselRefractiveValue, 0, wxALL, 5);
    vesselSizer->Add(vesselRefractiveSizer, 0, wxALL | wxEXPAND, 5);

    vesselSizer->Add(new wxStaticText(panel, wxID_ANY, "Цвет:"), 0, wxALL, 5);
    vesselSizer->Add(vesselColorChoice, 0, wxALL | wxEXPAND, 5);

    vesselLiquidSizer->Add(vesselSizer, 1, wxALL | wxEXPAND, 5);
    vesselLiquidSizer->Add(liquidSizer, 1, wxALL | wxEXPAND, 5);

    wxBoxSizer* rodOptionsSizer = new wxBoxSizer(wxVERTICAL);

    rodOptionsSizer->Add(rodSizer, 0, wxALL, 5);
    rodOptionsSizer->Add(optionsSizer, 0, wxALL | wxEXPAND, 5);

    rowSizer1->Add(vesselLiquidSizer, 1, wxALL | wxEXPAND, 5);
    rowSizer1->Add(rodOptionsSizer, 1, wxALL | wxEXPAND, 5);

    // Секция 2: Параметры камеры
    wxBoxSizer* cameraOptionsSizer = new wxBoxSizer(wxVERTICAL);

    // Поворот камеры
    wxStaticBox* cameraRotationBox = new wxStaticBox(panel, wxID_ANY, "Поворот камеры");
    wxStaticBoxSizer* cameraRotationSizer = new wxStaticBoxSizer(cameraRotationBox, wxVERTICAL);

    // Используем wxGridSizer для точного расположения кнопок
    wxGridSizer* rotationSizer = new wxGridSizer(3, 3, 5, 5);  // 3 строки, 3 столбца, расстояние 5 пикселей между элементами

    btnRotateForward = new wxButton(panel, wxID_ANY, "Вперед");
    btnRotateBackward = new wxButton(panel, wxID_ANY, "Назад");
    btnRotateLeft = new wxButton(panel, wxID_ANY, "Влево");
    btnRotateRight = new wxButton(panel, wxID_ANY, "Вправо");

    // Добавляем кнопки в сетку
    rotationSizer->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка
    rotationSizer->Add(btnRotateForward, 0, wxEXPAND);
    rotationSizer->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка

    rotationSizer->Add(btnRotateLeft, 0, wxEXPAND);
    rotationSizer->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка
    rotationSizer->Add(btnRotateRight, 0, wxEXPAND);

    rotationSizer->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка
    rotationSizer->Add(btnRotateBackward, 0, wxEXPAND);
    rotationSizer->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка

    // Добавляем сэйзер с кнопками в основной сэйзер
    cameraRotationSizer->Add(rotationSizer, 0, wxALL | wxEXPAND, 5);

    // Позиция камеры
    wxStaticBox* cameraPositionBox = new wxStaticBox(panel, wxID_ANY, "Позиция камеры");
    wxStaticBoxSizer* cameraPositionSizer = new wxStaticBoxSizer(cameraPositionBox, wxVERTICAL);

    // Используем wxGridSizer для точного расположения кнопок
    wxGridSizer* positionSizerCam = new wxGridSizer(3, 3, 5, 5);  // 3 строки, 3 столбца, расстояние 5 пикселей между элементами

    btnMoveForward = new wxButton(panel, wxID_ANY, "Вперед");
    btnMoveBackward = new wxButton(panel, wxID_ANY, "Назад");
    btnMoveLeft = new wxButton(panel, wxID_ANY, "Влево");
    btnMoveRight = new wxButton(panel, wxID_ANY, "Вправо");
    btnMoveUp = new wxButton(panel, wxID_ANY, "Вверх");
    btnMoveDown = new wxButton(panel, wxID_ANY, "Вниз");

    // Добавляем пустые элементы для ячеек, где "null"
    positionSizerCam->Add(btnMoveDown, 0, wxEXPAND);
    positionSizerCam->Add(btnMoveForward, 0, wxEXPAND);
    positionSizerCam->Add(btnMoveUp, 0, wxEXPAND);

    positionSizerCam->Add(btnMoveLeft, 0, wxEXPAND);
    positionSizerCam->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка
    positionSizerCam->Add(btnMoveRight, 0, wxEXPAND);

    positionSizerCam->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка
    positionSizerCam->Add(btnMoveBackward, 0, wxEXPAND);
    positionSizerCam->Add(new wxPanel(panel), 0, wxEXPAND);  // Пустая ячейка

    wxBoxSizer* rowSizer3 = new wxBoxSizer(wxVERTICAL);
    lightSizer->Add(new wxStaticText(panel, wxID_ANY, "Позиция источника света (X, Y, Z):"), 0, wxALL, 5);
    lightSizer->Add(positionSizer, 0, wxALL, 5);
    
    cameraPositionSizer->Add(positionSizerCam, 0, wxALL | wxEXPAND, 5);
    cameraOptionsSizer->Add(cameraRotationSizer, 0, wxALL | wxEXPAND, 5);
    cameraOptionsSizer->Add(cameraPositionSizer, 0, wxALL | wxEXPAND, 5);

    rowSizer3->Add(lightSizer, 0, wxALL, 5);
    rowSizer3->Add(cameraOptionsSizer, 0, wxALL, 5);
    rowSizer1->Add(rowSizer3, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(rowSizer1, 0, wxALL | wxEXPAND, 5);

    // Устанавливаем основной компоновщик
    panel->SetSizerAndFit(mainSizer);

    // Обработчики событий
    reflectivitySlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    transparencySlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    refractiveSlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    recursionSlider->Bind(wxEVT_SLIDER, &MyFrame::OnRecursionSliderUpdate, this);
    rodReflectivitySlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    vesselReflectivitySlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    vesselTransparencySlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    vesselRefractiveSlider->Bind(wxEVT_SLIDER, &MyFrame::OnSliderUpdate, this);
    vesselColorChoice->Bind(wxEVT_CHOICE, &MyFrame::OnColorChoice, this);
    rodColorChoice->Bind(wxEVT_CHOICE, &MyFrame::OnColorChoice, this);
    colorChoice->Bind(wxEVT_CHOICE, &MyFrame::OnColorChoice, this);

    xPos->Bind(wxEVT_KEY_DOWN, &MyFrame::OnEnterKey, this);
    yPos->Bind(wxEVT_KEY_DOWN, &MyFrame::OnEnterKey, this);
    zPos->Bind(wxEVT_KEY_DOWN, &MyFrame::OnEnterKey, this);

    updateButton->Bind(wxEVT_BUTTON, &MyFrame::OnUpdateImage, this);

    btnRotateForward->Bind(wxEVT_BUTTON, &MyFrame::OnCameraRotate, this);
    btnRotateBackward->Bind(wxEVT_BUTTON, &MyFrame::OnCameraRotate, this);
    btnRotateLeft->Bind(wxEVT_BUTTON, &MyFrame::OnCameraRotate, this);
    btnRotateRight->Bind(wxEVT_BUTTON, &MyFrame::OnCameraRotate, this);

    btnMoveForward->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);
    btnMoveBackward->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);
    btnMoveLeft->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);
    btnMoveRight->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);
    btnMoveUp->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);
    btnMoveDown->Bind(wxEVT_BUTTON, &MyFrame::OnCameraMove, this);

    panel->Bind(wxEVT_KEY_DOWN, &MyFrame::OnKeyDown, this);
}

void MyFrame::InitScene() {
    vec3 camPosition(0.0, 1.0, -6.0);
    camera.pos = camPosition;
    vec3 lightPosition(-10.0, 9.0, -5.0);
    light = Light(lightPosition);
    
    scene.light = light;
    scene.camera = camera;

    Cylinder vessel(
        vec3(0.0, 0.201, 0.0), 
        1.0, 1.2,
        ColorRGB(0.2, 0.2, 0.2), 
        Material(
            0.0, 0.0, 0.0, 
            0.1, 0.9, 1.49, 0.0, 
            2.0
        )
    );
    Cylinder liquid(
        vec3(0.0, -0.2, 0.0),
        0.99, 0.8,
        ColorRGB(0.06, 0.06, 0.43), 
        Material(
            0.0, 0.0, 0.0, 
            0.05, 0.8, 1.33, 0.0, 
            2.0
        )
    );
    Box rod(
        vec3(0.0, 1.2, 0.0), 
        vec3(0.3, 2.2, 0.3), 
        ColorRGB(0.06, 0.23, 0.06), 
        Material(
            0.5, 0.5, 0.5, 
            0.1, 0.0, 1.0, 0.2, 
            2.0
        )
    );
    Plane plane(
        -1.0, 
        ColorRGB(0.37, 0.19, 0.18), 
        Material(
            0.5, 0.5, 0.5, 
            0.1, 0.0, 0.0, 0.0, 
            2.0
        )
    );

    scene.addShape(std::make_shared<Cylinder>(liquid));
    scene.addShape(std::make_shared<Box>(rod));
    scene.addShape(std::make_shared<Cylinder>(vessel));
    scene.addShape(std::make_shared<Plane>(plane));
    
    renderer.SKYBOX = true;
    renderer.MAX_BOUNCES = 4;
}

void MyFrame::OnKeyDown(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();
    // Логика обработки нажатий
}

void MyFrame::OnEnterKey(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_RETURN)
        panel->SetFocus();
    else
        event.Skip();
}

void MyFrame::OnRecursionSliderUpdate(wxCommandEvent& event) {
    wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
    auto value = slider->GetValue();
    recursionValue->SetLabel(wxString::Format("%d", value));
    renderer.MAX_BOUNCES = value;
}

void MyFrame::OnColorChoice(wxCommandEvent& event) {
    wxChoice* ch = dynamic_cast<wxChoice*>(event.GetEventObject());
    int selectedIndex = ch->GetSelection();
    if (ch == rodColorChoice) {
        std::cout << ';' << selectedIndex;
        if (selectedIndex == 1)
            scene.Shapes[1]->color = ColorRGB(0.06, 0.06, 0.43);
        else if (selectedIndex == 2)
            scene.Shapes[1]->color = ColorRGB(0.2, 0.2, 0.2);
        else if (selectedIndex == 0)
            scene.Shapes[1]->color = ColorRGB(0.06, 0.43, 0.06);
        else if (selectedIndex == 3)
            scene.Shapes[1]->color = ColorRGB(0.43, 0.06, 0.06);
    }
    else if (ch == colorChoice) {
        std::cout << '+' << selectedIndex;
        if (selectedIndex == 0)
            scene.Shapes[0]->color = ColorRGB(0.06, 0.06, 0.23);
        else if (selectedIndex == 1)
            scene.Shapes[0]->color = ColorRGB(0.2, 0.2, 0.2);
        else if (selectedIndex == 2)
            scene.Shapes[0]->color = ColorRGB(0.06, 0.23, 0.06);
        else if (selectedIndex == 3)
            scene.Shapes[0]->color = ColorRGB(0.23, 0.06, 0.06);
    }
    else if (ch == vesselColorChoice) {
        std::cout << '-' << selectedIndex;
        if (selectedIndex == 1)
            scene.Shapes[2]->color = ColorRGB(0.06, 0.06, 0.23);
        else if (selectedIndex == 0)
            scene.Shapes[2]->color = ColorRGB(0.2, 0.2, 0.2);
        else if (selectedIndex == 2)
            scene.Shapes[2]->color = ColorRGB(0.06, 0.23, 0.06);
        else if (selectedIndex == 3)
            scene.Shapes[2]->color = ColorRGB(0.23, 0.06, 0.06);
    }
}

void MyFrame::OnSliderUpdate(wxCommandEvent& event) {
    wxSlider* slider = dynamic_cast<wxSlider*>(event.GetEventObject());
    wxStaticText* valueText = NULL;

    if (slider == reflectivitySlider) {
        valueText = reflectivityValue;
        float value = slider->GetValue() / 100.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[0]->material.reflectivity = value;
    }
    else if (slider == transparencySlider) {
        valueText = transparencyValue;
        float value = slider->GetValue() / 100.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[0]->material.transparency = value;
    }
    else if (slider == refractiveSlider) {
        valueText = refractiveValue;
        float value = slider->GetValue() / 10.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[0]->material.refractiveIndex = value;
    }
    else if (slider == rodReflectivitySlider) {
        valueText = rodReflectivityValue;
        float value = slider->GetValue() / 100.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[1]->material.reflectivity = value;
    }
    else if (slider == vesselReflectivitySlider) {
        valueText = vesselReflectivityValue;
        float value = slider->GetValue() / 100.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[2]->material.reflectivity = value;
    }
    else if (slider == vesselTransparencySlider) {
        valueText = vesselTransparencyValue;
        float value = slider->GetValue() / 100.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[2]->material.transparency = value;
    }
    else if (slider == vesselRefractiveSlider) {
        valueText = vesselRefractiveValue;
        float value = slider->GetValue() / 10.0;
        valueText->SetLabel(wxString::Format("%.2f", value));
        scene.Shapes[2]->material.refractiveIndex = value;
    }
}

void MyFrame::OnUpdateImage(wxCommandEvent& event) {
    // Получаем строки из wxTextCtrl
    wxString xStr = xPos->GetValue();
    wxString yStr = yPos->GetValue();
    wxString zStr = zPos->GetValue();

    try {
        float x = std::stof(xStr.ToStdString());
        float y = std::stof(yStr.ToStdString());
        float z = std::stof(zStr.ToStdString());

        if (std::abs(x) > 20.0f || std::abs(y) > 20.0f || std::abs(z) > 20.0f) {
            throw std::out_of_range("Значение x, y или z слишком велико (больше 20 по модулю).");
        }
        xPos->SetValue(wxString::Format("%.2f", x));
        yPos->SetValue(wxString::Format("%.2f", y));
        zPos->SetValue(wxString::Format("%.2f", z));
        scene.light.pos = vec3(x, y, z);
    }
    catch (const std::invalid_argument& e) {
        xPos->SetValue(wxString::Format("%.2f", scene.light.pos.x));
        yPos->SetValue(wxString::Format("%.2f", scene.light.pos.y));
        zPos->SetValue(wxString::Format("%.2f", scene.light.pos.z));
        wxMessageBox("Ошибка: неверный формат ввода. Пожалуйста, введите числовое значение.", "Ошибка", wxOK | wxICON_ERROR);
        return;
    }
    catch (const std::out_of_range& e) {
        xPos->SetValue(wxString::Format("%2f", scene.light.pos.x));
        yPos->SetValue(wxString::Format("%2f", scene.light.pos.y));
        zPos->SetValue(wxString::Format("%2f", scene.light.pos.z));
        wxMessageBox("Ошибка: введенное значение выходит за пределы допустимого диапазона.", "Ошибка", wxOK | wxICON_ERROR);
        return;
    }
    auto data = renderer.renderScene(&scene, WIDTH, HEIGHT);
    cv::Mat img(HEIGHT, WIDTH, CV_8UC3);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int idx = y * WIDTH + x;
            ColorRGB pixel = data[idx];
            img.at<cv::Vec3b>(y, x) = cv::Vec3b(pixel.b * 255.0f, pixel.g * 255.0f, pixel.r * 255.0f);
        }
    }
    bool isNoiseChecked = noiseCheckBox->IsChecked();
    bool isSmoothingChecked = smoothingCheckBox->IsChecked();

    cv::resize(img, img, cv::Size(WIDTH, HEIGHT), WIDTH * 5, HEIGHT * 5, cv::INTER_LINEAR);
    if (isSmoothingChecked)
        cv::GaussianBlur(img, img, cv::Size(3, 3), 0);
    if (isNoiseChecked) {
        cv::Mat noise(img.size(), img.type());
        cv::randn(noise, 0, 3);
        img += noise;
    }
    cv::resize(img, img, cv::Size(WIDTH, HEIGHT), WIDTH * (1/5), HEIGHT * (1/5), cv::INTER_LINEAR);
    std::string outputPath = "output_image.png"; // Путь для сохранения
    if (!cv::imwrite(outputPath, img)) {
        wxMessageBox("Ошибка: не удалось сохранить изображение.", "Ошибка", wxOK | wxICON_ERROR);
    }
    cv::imshow("", img);
    cv::waitKey(0);
}

void MyFrame::OnCameraMove(wxCommandEvent& event) {
    int id = event.GetId();

    if (id == btnMoveForward->GetId()) {
        scene.camera.pos.z += 0.3;
    } else if (id == btnMoveBackward->GetId()) {
        scene.camera.pos.z -= 0.3;
    } else if (id == btnMoveLeft->GetId()) {
        scene.camera.pos.x -= 0.3;
    } else if (id == btnMoveRight->GetId()) {
        scene.camera.pos.x += 0.3;
    } else if (id == btnMoveUp->GetId()) {
        scene.camera.pos.y += 0.3;
    } else if (id == btnMoveDown->GetId()) {
        scene.camera.pos.y -= 0.3;
    }
}

void MyFrame::OnCameraRotate(wxCommandEvent& event) {
    int id = event.GetId();

    if (id == btnRotateForward->GetId()) {
        scene.camera.pitch += 10;
        auto camPos = scene.camera.pos;
        scene.camera.trl(camPos.rot(0.0f, scene.camera.pitch).mul(1.0 / 50.0f));
    } else if (id == btnRotateBackward->GetId()) {
        scene.camera.pitch -= 10;
        auto camPos = scene.camera.pos;
        scene.camera.trl(camPos.rot(0.0f, scene.camera.pitch).mul(1.0 / 50.0f));
    } else if (id == btnRotateLeft->GetId()) {
        scene.camera.yaw -= 10;
        auto camPos = scene.camera.pos;
        scene.camera.trl(camPos.rot(scene.camera.yaw, 0.0f).mul(1.0 / 50.0f));
    } else if (id == btnRotateRight->GetId()) {
        scene.camera.yaw += 10;
        auto camPos = scene.camera.pos;
        scene.camera.trl(camPos.rot(scene.camera.yaw, 0.0f).mul(1.0 / 50.0f));
    }
}