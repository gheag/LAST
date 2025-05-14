#include "ini.h"

using namespace sf;
using namespace std;

// адрес контроллера, порт модбас (создаем обьект класса modbus)
modbus plc = modbus("192.168.11.56", 502);;

// шрифт
const sf::Font font("segoeui.ttf"); // шрифт текста


void wtf_select(int butt_code, Vector2i mouse_localPosition) {

    int x = butt_setings[butt_code][2];
    int y = butt_setings[butt_code][3];

    if (mouse_localPosition.x >= x && mouse_localPosition.x <= x + butt_setings[butt_code][5] && mouse_localPosition.y >= y && mouse_localPosition.y <= y + butt_setings[butt_code][4]) {
        butt_setings[butt_code][6] = 1;
    }
    else{ butt_setings[butt_code][6]=0; }
}

/*Функция чтения статуса по модбас*/                    uint16_t read_stats(uint16_t adress) { // функция чтения статуса
    uint16_t stat;
    plc.modbus_connect();
    plc.modbus_read_input_registers(adress, 1, &stat);
    plc.modbus_close();

    return stat;
}

/*Функция подключения по модбас*/                       void connect_on() {
    plc.modbus_connect();
}

/*Функция отключения по модбас*/                        void connect_off() {
    plc.modbus_close();
}

/*Функция обработки ввода*/                             std::string input_text(int butt_numm, Event::KeyPressed keyPressed, std::string new_str) {
    if (new_str.size() < 4) {
        switch (keyPressed.scancode) {

        case sf::Keyboard::Scancode::Num0: {
            if(new_str!="0") {
                new_str += "0";
            }
            else{ new_str="0"; }
        } break;

        case sf::Keyboard::Scancode::Num1: {
            if (new_str != "0") {
                new_str += "1";
            }
            else { new_str = "1"; }
        } break;

        case sf::Keyboard::Scancode::Num2: {
            if (new_str != "0") {
                new_str += "2";
            }
            else { new_str = "2"; }
        } break;

        case sf::Keyboard::Scancode::Num3: {
            if (new_str != "0") {
                new_str += "3";
            }
            else { new_str = "3"; }
        } break;

        case sf::Keyboard::Scancode::Num4: {
            if (new_str != "0") {
                new_str += "4";
            }
            else { new_str = "4"; }
        } break;

        case sf::Keyboard::Scancode::Num5: {
            if (new_str != "0") {
                new_str += "5";
            }
            else { new_str = "5"; }
        } break;

        case sf::Keyboard::Scancode::Num6: {
            if (new_str != "0") {
                new_str += "6";
            }
            else { new_str = "6"; }
        } break;

        case sf::Keyboard::Scancode::Num7: {
            if (new_str != "0") {
                new_str += "7";
            }
            else { new_str = "7"; }
        } break;

        case sf::Keyboard::Scancode::Num8: {
            if (new_str != "0") {
                new_str += "8";
            }
            else { new_str = "8"; }
        } break;

        case sf::Keyboard::Scancode::Num9: {
            if (new_str != "0") {
                new_str += "9";
            }
            else { new_str = "9"; }
        } break;

        case sf::Keyboard::Scancode::Backspace: {
            if (new_str.length() > 1) {
                new_str.pop_back();
            }
            else { new_str = "0"; }
        } break;  

        case sf::Keyboard::Scancode::Enter: {
                can_input[butt_numm] = 0;
        } break;

        }
    }
    else {
        switch (keyPressed.scancode) {
            case sf::Keyboard::Scancode::Backspace: {
                if (new_str.length() > 1) {
                   new_str.pop_back();
                }
                 else { new_str = "0"; }
            } break;

            case sf::Keyboard::Scancode::Enter: {
                can_input[butt_numm] = 0;
            } break;
        }
    }
    
    if (new_str.size() < 1) { new_str = "0"; }
    return new_str;
}

/*Функция проверки в зоне ли кнопки курсор*/            bool is_iside(int butt_code, Vector2i mouse_localPosition) {
    wtf_select(butt_code, mouse_localPosition);
    if ((butt_setings[butt_code][6])) {
        inshape = 1;
    }
    else {
        inshape = 0;
    }
    return inshape;
}

/*Класс кнопки*/                                        class Buttom {

public:
    RectangleShape butt_Shape;

    int butt_num;

    int label_posx, label_posy;

    RectangleShape init(int posx, int posy, int height, int width, int color_R, int color_G, int color_B, int color_transparency) {

        butt_setings[butt_num][1] = butt_num; // номер кнопки
        butt_setings[butt_num][2] = posx;     // координата по x
        butt_setings[butt_num][3] = posy;     // координата по y
        butt_setings[butt_num][4] = height;   // высота
        butt_setings[butt_num][5] = width;    // ширина

        // создание формы
        RectangleShape butt_name;
        butt_name.setSize(Vector2f(width, height));        // размер кнопки
        butt_name.setPosition(Vector2f(posx, posy));       // позиция кнопки
        butt_name.setFillColor(Color(color_R, color_G, color_B, color_transparency));

        return butt_name;
    }

   Vector2f label_place() {
        label_posx = butt_setings[butt_num][2]+16;
        label_posy = butt_setings[butt_num][3]+3;

        Vector2f label_pos(label_posx, label_posy);

        return label_pos;
    }

};

/*Функция создания лейбла*/                             Text label_create(int num, bool can_input, std::string label_name) {
    Buttom bt;
    Text butt_label(font);                                           // создание текста
    bt.butt_num = num;
    String label_text;

    Vector2f label_place = bt.label_place();
    butt_label.setPosition(Vector2f(label_place.x, label_place.y));  // позиция метки
    if (can_input) {
        butt_label.setString(label_text);                            // текст метки
    }
    else {
        butt_label.setString(label_name);                            // текст метки
    }
                                   
    butt_label.setFillColor(Color::Black);                           // цвет текста


    return butt_label;
}

/*Функция отключения выделения*/                        void select_off() {
    for (int i = 0; i < 25; ++i) {
        can_input[i] = 0;
    }
}

/*Функция записи coil*/                                 void write_coil(uint16_t address, bool true_false){
    connect_on();
    plc.modbus_write_coil(address, true_false);
    connect_off();
}

/*Функция записи регистров*/                            void write_reg(uint16_t address, uint16_t val) {
    connect_on();
    plc.modbus_write_register(address, val);    
    connect_off();
}

/*Функция чтения холдинг регистров*/                    void read_holdings(uint16_t address, uint16_t *val) {
    connect_on();
    plc.modbus_read_holding_registers(address,1, val);
    connect_off();
}

/*Функция чтения инпут регистров*/                      void read_inputs(uint16_t address, uint16_t* val) {
    connect_on();
    plc.modbus_read_input_registers(address, 1, val);
    connect_off();
}

/*Функция перезаписи всех уставок разом*/               void set_setpoints() {
    connect_on();

    plc.modbus_write_register(30, setpoints[butt_setings[2][1]]); //       Тmin  00030  

    plc.modbus_write_register(31, setpoints[butt_setings[3][1]]); //       Tmax  00031

    plc.modbus_write_register(32, setpoints[butt_setings[8][1]]); //       Фреон_ВК     00032

    plc.modbus_write_register(34, setpoints[butt_setings[9][1]]); //       Фреон_НК     00034

    plc.modbus_write_register(35, setpoints[10]);                 //       Пер.ВК_РО    00035

    plc.modbus_write_register(36, setpoints[11]);                 //       Пер.ВК_КДИ   00036

    plc.modbus_write_register(39, setpoints[12]);                 //       Пер.НК_РО    00039

    plc.modbus_write_register(40, setpoints[13]);                 //       Р_СК_РП_ВК   00040

    plc.modbus_write_register(42, setpoints[14]);                 //       Р_СК_РП_НК   00042

    plc.modbus_write_register(43, setpoints[15]);                 //       Т_СК_ОХ_ВК   00043  

    plc.modbus_write_register(45, setpoints[16]);                 //       Т_СК_ОХ_НК   00045

    plc.modbus_write_register(46, setpoints[17]);                 //       ОКНО Т       00046

    plc.modbus_write_register(47, setpoints[18]);                 //       Период Т     00047

    plc.modbus_write_register(48, setpoints[19]);                 //       Дифф_С       00048

    plc.modbus_write_register(49, setpoints[20]);                 //       Дифф_Множ    00049

    plc.modbus_write_register(50, setpoints[21]);                 //       Фаза_Ошиб    00050

    plc.modbus_write_register(51, setpoints[22]);                 //       Фаза произ   00051

    plc.modbus_write_register(52, setpoints[23]);                 //       Фаза ЕН      00052

    plc.modbus_write_register(53, setpoints[24]);                 //       Фаза ЕО      00053
    connect_off();
}

/*Функция действия при запущенном таймере*/             void timer_event() {
    if (!first_timer_compl && !timer_start) { cout << "\n" << " таймер не работает"; }
    else {
        if (timer_start && !first_timer_compl) {
            system("cls");
            cout << "\n" << " таймер считает";

            normirovannaya_proizv = read_stats(00142);                                                  // 00098 (00142) нормированная производная
            if (abs(normirovannaya_proizv) > abs(old_proizv)) { old_proizv = normirovannaya_proizv; }   // выбираем наибольшее по модулю значение
        }
        else {
            if (timer_start && first_timer_compl) {
                system("cls");
                cout << "\n" << " таймер посчитал";
                timer_start = 0;
            }
        }
    }
}

/*Функция главного потока*/                             void first_thrand() {

    // Окно
    RenderWindow window(VideoMode({ 800, 800 }), "SFML_MODBUS");

    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(CP_UTF8);

    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(45);
    window.setActive(true);


    //////// скрыть консоль ////////
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    ////////////////////////////////

    // set slave id (адрес в сети модбас)
    plc.modbus_set_slave_id(1);

    for (int ii = 0; ii < 25; ++ii) {
        can_input[ii] = 0;
    }

    // создание кнопок //

    //////////////// кнопка старт ///////////
    Buttom bt_1;
    RectangleShape butt_1;
    Text butt_1_label(font);                                               // создание текста
    bt_1.butt_num = 1;

    butt_1 = bt_1.init(400, 600, 50, 100, 100, 100, 100, 170);

    butt_1_label = label_create(1, false, "start");
    //////////////////////////////////////////////////////



    //////////////// поле ввода Tmin ///////////
    Buttom bt_2;
    RectangleShape butt_2;
    Text butt_2_label(font);                                               // создание текста
    butt_2_label;
    bt_2.butt_num = 2;
    std::string label_2_text;

    butt_2 = bt_2.init(150, 300, 50, 100, 200, 200, 250, 200);
    butt_2.setOutlineColor(Color(225, 105, 105, 95));                      // цвет обводки

    butt_2_label = label_create(2, true, "Tmin");
    //////////////////////////////////////////////////////


    //////////////// поле ввода Tmax ///////////
    Buttom bt_3;
    RectangleShape butt_3;
    Text butt_3_label(font);                                               // создание текста
    bt_3.butt_num = 3;
    std::string label_3_text;

    butt_3 = bt_3.init(150, 400, 50, 100, 200, 200, 250, 200);
    butt_3.setOutlineColor(Color(225, 105, 105, 95));

    butt_3_label = label_create(3, true, "Tmax");
    //////////////////////////////////////////////////////

    //////////////// поле ввода FreonVK ///////////
    Buttom bt_8;
    RectangleShape butt_8;
    Text butt_8_label(font);                                               // создание текста
    bt_8.butt_num = 8;
    std::string label_8_text;

    butt_8 = bt_8.init(150, 500, 50, 100, 200, 200, 250, 200);
    butt_8.setOutlineColor(Color(225, 105, 105, 95));

    butt_8_label = label_create(8, true, "FreonVK");
    //////////////////////////////////////////////////////


    //////////////// поле ввода FreonNK ///////////
    Buttom bt_9;
    RectangleShape butt_9;
    Text butt_9_label(font);                                               // создание текста
    bt_9.butt_num = 9;
    std::string label_9_text;

    butt_9 = bt_9.init(150, 600, 50, 100, 200, 200, 250, 200);
    butt_9.setOutlineColor(Color(225, 105, 105, 95));

    butt_9_label = label_create(9, true, "FreonNK");
    //////////////////////////////////////////////////////


    //////////////// поле ввода IP ///////////

    int ip_posx = 200;
    int ip_posy = 100;

    int ip_1_num = 4;
    int ip_2_num = 5;
    int ip_3_num = 6;
    int ip_4_num = 7;

    Buttom IP_bt_1;
    RectangleShape IP_butt_1;
    Text butt_IP1_label(font);                                               // создание текста
    IP_bt_1.butt_num = ip_1_num;
    std::string label_4_text;

    IP_butt_1 = IP_bt_1.init(ip_posx, ip_posy, 50, 100, 150, 220, 200, 90);
    IP_butt_1.setOutlineColor(Color(220, 200, 100, 100));

    butt_IP1_label = label_create(4, true, "ip1");

    Buttom IP_bt_2;
    RectangleShape IP_butt_2;
    Text butt_IP2_label(font);                                               // создание текста
    IP_bt_2.butt_num = ip_2_num;
    std::string label_5_text;

    IP_butt_2 = IP_bt_2.init(ip_posx + 110, ip_posy, 50, 100, 150, 220, 200, 90);
    IP_butt_2.setOutlineColor(Color(220, 200, 100, 100));

    butt_IP2_label = label_create(5, true, "ip2");

    Buttom IP_bt_3;
    RectangleShape IP_butt_3;
    Text butt_IP3_label(font);                                               // создание текста
    IP_bt_3.butt_num = ip_3_num;
    std::string label_6_text;

    IP_butt_3 = IP_bt_3.init(ip_posx + 220, ip_posy, 50, 100, 150, 220, 200, 90);
    IP_butt_3.setOutlineColor(Color(220, 200, 100, 100));

    butt_IP3_label = label_create(6, true, "ip3");

    Buttom IP_bt_4;
    RectangleShape IP_butt_4;
    Text butt_IP4_label(font);                                               // создание текста
    IP_bt_4.butt_num = ip_4_num;
    std::string label_7_text;

    IP_butt_4 = IP_bt_4.init(ip_posx + 330, ip_posy, 50, 100, 150, 220, 200, 90);
    IP_butt_4.setOutlineColor(Color(220, 200, 100, 100));

    butt_IP4_label = label_create(7, true, "ip4");

    ////////////////////////////////////////////////////////

   // Текст //

    Text label_10(font); // Надпись "IP"
    label_10 = label_create(10, false, "IP");
    label_10.setPosition(Vector2f(ip_posx - 50, ip_posy));

    Text label_11(font); // Надпись "УСТАВКИ"
    label_11 = label_create(11, false, "SetPoints");
    label_11.setPosition(Vector2f(135, 230));

    Text label_12(font); // Надпись "Tmin"
    label_12 = label_create(12, false, "Tmin");
    label_12.setPosition(Vector2f(butt_setings[2][2] - 90, butt_setings[2][3]));

    Text label_13(font); // Надпись "Tmax"
    label_13 = label_create(13, false, "Tmax");
    label_13.setPosition(Vector2f(butt_setings[3][2] - 90, butt_setings[3][3]));

    Text label_14(font); // Надпись "Фреон_ВК"
    label_14 = label_create(14, false, "FreonVK");
    label_14.setPosition(Vector2f(butt_setings[8][2] - 130, butt_setings[8][3]));

    Text label_15(font); // Надпись "Фреон_НК"
    label_15 = label_create(15, false, "FreonNK");
    label_15.setPosition(Vector2f(butt_setings[9][2] - 130, butt_setings[9][3]));

    //////////////////////////////////////////////////////////

        // пока открыто окно выполнять логику и отслеживать ивенты //
    while (window.isOpen()) {

        ip = ip1 + "." + ip2 + "." + ip3 + "." + ip4; // формируем строку ip адреса 
        plc = modbus(ip, 502); // передаем ip

        // отслеживаем положение курсора //
        Vector2i mouse_localPosition = Mouse::getPosition(window);

        /*СТАТУСЫ*/
                // считываю статус 00 //
        uint16_t stat_00;
        stat_00 = read_stats(00000);
        std::bitset<16> bitset_stat_00 = stat_00;
        /////////////////////////////////////////

        // считываю статус 01 //
        uint16_t stat_01;
        stat_01 = read_stats(00001);
        std::bitset<16> bitset_stat_01 = stat_01;
        /////////////////////////////////////////

        // считываю статус 02 //
        uint16_t stat_02;
        stat_02 = read_stats(00002);
        std::bitset<16> bitset_stat_02 = stat_02;
        /////////////////////////////////////////

        // считываю статус 03 //
        uint16_t stat_03;
        stat_03 = read_stats(00003);
        std::bitset<16> bitset_stat_03 = stat_03;
        /////////////////////////////////////////
/////////

        // анализируем начало настройки //
        is_start = bitset_stat_00.test(2); // проверяем статус работы (второй бит статус 00)


        if (is_start) {
            butt_1_label.setFillColor(Color::Red);
        }
        else {
            butt_1_label.setFillColor(Color::Black);
            flag_setpoint = 0;
            timer_start = 0;
            first_timer_compl = false;
        }


        // обработчик ивентов //
        while (const std::optional event = window.pollEvent()) {

////////////// Взаимодействие с кнопками //


/*START*/   bool start_shape = is_iside(butt_setings[1][1], mouse_localPosition);
            if (start_shape) {
                if (event->is<Event::MouseButtonReleased>()) {
                    if (!is_start) {
                        write_coil(00000, one);
                        Sleep(200);
                        write_coil(00000, zero);
                        flag_butt_start = 1;
                    }
                    else {
                        write_coil(00002, one);
                        Sleep(200);
                        write_coil(00002, zero);
                    }
                }
            }

            /*input_Тmin*/ bool Tmin_shape = is_iside(butt_setings[2][1], mouse_localPosition);
            if (Tmin_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[2][1]] = 1;
            }
            if (can_input[butt_setings[2][1]]) {
                butt_2.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_2_text = input_text(2, *keyPressed, label_2_text);
                    butt_2_label.setString(label_2_text);
                    setpoints[butt_setings[2][1]] = std::stoi(label_2_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                butt_2.setOutlineThickness(0);
            }


            /*input_Тmax*/ bool Tmax_shape = is_iside(butt_setings[3][1], mouse_localPosition);
            if (Tmax_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[3][1]] = 1;
            }
            if (can_input[butt_setings[3][1]]) {
                butt_3.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_3_text = input_text(3, *keyPressed, label_3_text);
                    butt_3_label.setString(label_3_text);
                    setpoints[butt_setings[3][1]] = std::stoi(label_3_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                butt_3.setOutlineThickness(0);
            }


            /*input_IP*/    bool IP_1_shape = is_iside(butt_setings[ip_1_num][1], mouse_localPosition);
            if (IP_1_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[ip_1_num][1]] = 1;
            }
            if (can_input[butt_setings[ip_1_num][1]]) {
                IP_butt_1.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_4_text = input_text(4, *keyPressed, label_4_text);
                    butt_IP1_label.setString(label_4_text);
                    setpoints[ip_1_num] = std::stoi(label_4_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                IP_butt_1.setOutlineThickness(0);
                ip1 = label_4_text;
            }


            bool IP_2_shape = is_iside(butt_setings[ip_2_num][1], mouse_localPosition);
            if (IP_2_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[ip_2_num][1]] = 1;
            }
            if (can_input[butt_setings[ip_2_num][1]]) {
                IP_butt_2.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_5_text = input_text(5, *keyPressed, label_5_text);
                    butt_IP2_label.setString(label_5_text);
                    setpoints[ip_2_num] = std::stoi(label_5_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                IP_butt_2.setOutlineThickness(0);
                ip2 = label_5_text;
            }


            bool IP_3_shape = is_iside(butt_setings[ip_3_num][1], mouse_localPosition);
            if (IP_3_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[ip_3_num][1]] = 1;
            }
            if (can_input[butt_setings[ip_3_num][1]]) {
                IP_butt_3.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_6_text = input_text(6, *keyPressed, label_6_text);
                    butt_IP3_label.setString(label_6_text);
                    setpoints[ip_3_num] = std::stoi(label_6_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                IP_butt_3.setOutlineThickness(0);
                ip3 = label_6_text;
            }


            bool IP_4_shape = is_iside(butt_setings[ip_4_num][1], mouse_localPosition);
            if (IP_4_shape && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[ip_4_num][1]] = 1;
            }
            if (can_input[butt_setings[ip_4_num][1]]) {
                IP_butt_4.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_7_text = input_text(7, *keyPressed, label_7_text);
                    butt_IP4_label.setString(label_7_text);
                    setpoints[ip_4_num] = std::stoi(label_7_text);
                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                IP_butt_4.setOutlineThickness(0);
                ip4 = label_7_text;
            }
            /////////////////////////////////////////////////////////////////////////////////////////////


            /*input_FreonVK*/ bool FreonVK = is_iside(butt_setings[8][1], mouse_localPosition);
            if (FreonVK && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[8][1]] = 1;
            }
            if (can_input[butt_setings[8][1]]) {
                butt_8.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_8_text = input_text(8, *keyPressed, label_8_text);
                    butt_8_label.setString(label_8_text);
                    setpoints[butt_setings[8][1]] = std::stoi(label_8_text);

                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                butt_8.setOutlineThickness(0);
            }


            /*input_FreonNK*/ bool FreonNK = is_iside(butt_setings[9][1], mouse_localPosition);
            if (FreonNK && (event->is<Event::MouseButtonReleased>())) {
                select_off();
                can_input[butt_setings[9][1]] = 1;
            }
            if (can_input[butt_setings[9][1]]) {
                butt_9.setOutlineThickness(4);
                if (auto keyPressed = event->getIf<Event::KeyPressed>()) {
                    label_9_text = input_text(9, *keyPressed, label_9_text);
                    butt_9_label.setString(label_9_text);
                    setpoints[butt_setings[9][1]] = std::stoi(label_9_text);

                }
            }
            else {
                mouse_localPosition = Mouse::getPosition(window); // нужно обновить координаты мыши чтобы избежать бага когда мышь передвинули, а координаты старые
                butt_9.setOutlineThickness(0);
            }


            /* ивент закрытие окна */    if (event->is<Event::Closed>()) {
                plc.modbus_close(); // отключение modbus
                window.close(); // закрытие окна
            }
            /////////////////////////////////////////

            if (is_start) {
                // * ОБОЗНАЧАЕТ ЧТО ЭТИ ПАРАМЕТРЫ ТРЕБУЕТСЯ ВВЕСТИ В РУЧНУЮ
                // 1) записываем первичные настройки в ПЛК 
                //      (
                //          Holding_Reg
                //       Тmin*      00030 (30)   /
                //       Tmax*      00031 (31)   /
                //       Фреон_ВК*  00032 (32)   / 
                //       Фреон_НК*  00034 (34)   / 
                //       Пер.ВК_РО  00035        / 
                //       Пер.ВК_КДИ 00036        / 
                //       Пер.НК_РО  00039        /
                //       Р_СК_РП_ВК 00040        / 
                //       Р_СК_РП_НК 00042        /
                //       Т_СК_ОХ_ВК 00043        /_
                //       Т_СК_ОХ_НК 00045        /
                //       ОКНО Т     00046        /
                //       Период Т   00047        /
                //       Дифф_С     00048        /   
                //       Дифф_Множ  00049        /
                //       Фаза_Ошиб  00050        /
                //       Фаза произ 00051        /
                //       Фаза ЕН    00052        /
                //       Фаза ЕО    00053        /
                // )
                // 3) запускаем камеру на крайнюю точку (Tmax 00031) (Т уставки 00097)
                // 4) через N минут считать фазу производной (Input_Reg  00098 (0x0062..0x0066))
                //      a) считывать нужно в течении некоторого времени (записываем наибольшее по модулю) 
                // 5) записать модуль фазы производной в регистр (Holding_Reg   00051  (0x0033))
                // 6) запускаем камеру на другую крайнюю точку (Tmin 00030)
                // 7) через N минут считать фазу производной
                // 8) если фаза больше выставленной, то заменяем
                // 9) по завершении вывести что настройка завершена


                if (!flag_setpoint) { // при запуске записать уставки в ПЛК
                    set_setpoints();

                    faza_proizv_complite = 0;
                    flag_setpoint = 1;
                }
                // Запуск камеры на Tmax и Tmin//
                timer_start = 1;
                if (!Tmax_step_complite && Tmax_step_complite<2) {
                    write_reg(97, setpoints[butt_setings[3][1]]); // записываем Тmax как уставку температуры
                    timer_event();
                    if (first_timer_compl) { Tmax_step_complite = 1; first_timer_compl = 0; }
                }
                else {
                    write_reg(97, setpoints[butt_setings[2][1]]);// записываем Тmin как уставку температуры
                    timer_event();
                    if (first_timer_compl) { Tmax_step_complite = 2; first_timer_compl = 0; }
                }
                if (Tmax_step_complite == 2 && !faza_proizv_complite) {
                    system("cls");
                    cout << "\n" << " Фаза производной настроена";
                    faza_proizv_complite = 1;
                    last = 1;
                }
                last = 1;
            }
        }

        window.clear(Color(245, 250, 252, 200));

        //std::cout << ip << "\n";

        window.draw(butt_1);
        window.draw(butt_1_label);

        window.draw(butt_2);
        window.draw(butt_2_label);

        window.draw(butt_3);
        window.draw(butt_3_label);

        window.draw(IP_butt_1);
        window.draw(butt_IP1_label);
        window.draw(IP_butt_2);
        window.draw(butt_IP2_label);
        window.draw(IP_butt_3);
        window.draw(butt_IP3_label);
        window.draw(IP_butt_4);
        window.draw(butt_IP4_label);

        window.draw(butt_8);
        window.draw(butt_8_label);

        window.draw(butt_9);
        window.draw(butt_9_label);

        window.draw(label_10);

        window.draw(label_11);

        window.draw(label_12);

        window.draw(label_13);

        window.draw(label_14);

        window.draw(label_15);

        window.display();
    }
}


void timer() {
    while (!last) {
        if (timer_start) {
            Sleep(10000);
            first_timer_compl = true;
        }
    }
}


int main(){
    thread main_thread(first_thrand);
    thread TON(timer);

    TON.join(); 
    main_thread.join();

    return 0;
}



