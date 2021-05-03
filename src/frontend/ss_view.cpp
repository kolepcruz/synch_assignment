#include "ss_view.hpp"

int get_leitos() {
    int leitos, y, x;
    string number;
    while (1) {
        leitos = getch();
        if (leitos == 10) {
            if (number.size() > 0) {
                printw("\nEssa é a sua string: %s", number);
                break;
            }
        } else if (leitos == 127) {
            getyx(stdscr, y, x);
            move(y, x - 1);
            printw(" ");
            move(y, x - 1);
        } else {
            if (isdigit(leitos)) {
                number.append(to_string(leitos));
            }
            printw("%c", leitos);
        }
    }
    clear();
    return leitos;
}

int get_lutadores() {
    int lutadores;
    while (1) {
        lutadores = getch();
        if (lutadores == 10) {
            break;
        }
        printw("%c", lutadores);
    }
    clear();
    return lutadores;
}

void desenhaLeito(WINDOW* enfermaria, int n_leitos) {
    int width_enf, height_enf;
    int margin_x, margin_y, dist_x, dist_y, n_lin, n_col;
    getmaxyx(enfermaria, height_enf, width_enf);

    float ratio = (float)((float)height_enf / width_enf);

    n_col = round(sqrt((float)n_leitos / ratio));
    n_lin = ceil(ratio * n_col);

    margin_x = dist_x = width_enf / (n_col + 1);
    margin_y = dist_y = height_enf / (n_lin + 1);

    for (int i = 1; i <= n_col; i++) {
        for (int j = 1; j <= n_lin; j++) {
            if (n_col * (j - 1) + i <= n_leitos) {
                // subtract i by -1 because the warriors will be at second pos.
                if (has_colors()) {
                    wattron(enfermaria, COLOR_PAIR(2));
                    mvwprintw(enfermaria, j * margin_y, i * margin_x - 1,
                              "___/");
                    wattroff(enfermaria, COLOR_PAIR(2));
                } else {
                    wattron(enfermaria, A_REVERSE);
                    mvwprintw(enfermaria, j * margin_y, i * margin_x - 1,
                              "___/");
                    wattroff(enfermaria, A_REVERSE);
                }
            }
        }
    }
    wrefresh(enfermaria);
}

void desenhaLutadores(WINDOW* ringue, int n_lut) {
    int width_ringue, height_ringue;
    int margin_x, margin_y, dist_x, dist_y, n_lin, n_col;
    getmaxyx(ringue, height_ringue, width_ringue);
    float ratio = (float)((float)height_ringue / width_ringue);

    n_col = round(sqrt((float)n_lut / ratio));
    n_lin = ceil(ratio * n_col);

    margin_x = dist_x = width_ringue / (n_col + 1);
    margin_y = dist_y = height_ringue / (n_lin + 1);

    for (int i = 1; i <= n_col; i++) {
        for (int j = 1; j <= n_lin; j++) {
            if (n_col * (j - 1) + i <= n_lut) {
                if ((i + j) % 2 == 1) {
                    wattron(ringue, COLOR_PAIR(3));
                    mvwprintw(ringue, j * margin_y, i * margin_x, "O");
                    wattroff(ringue, COLOR_PAIR(3));
                } else {
                    wattron(ringue, COLOR_PAIR(4));
                    mvwprintw(ringue, j * margin_y, i * margin_x, "E");
                    wattroff(ringue, COLOR_PAIR(4));
                }
            }
        }
    }
    wrefresh(ringue);
}

void intro() {
    ui ini_x_saiyadin = 5;
    ui ini_x_name = 10;
    mvprintw(00, ini_x_saiyadin,
             " .d8888b.                                          .d8888b.      "
             "     d8b                      d8b d8b                  ");
    mvprintw(01, ini_x_saiyadin,
             "d88P  Y88b                                        d88P  Y88b     "
             "     Y8P                      Y8P Y8P                  ");
    mvprintw(02, ini_x_saiyadin,
             "Y88b.                                             Y88b.          "
             "                                                       ");
    mvprintw(03, ini_x_saiyadin,
             " 'Y888b.   888  888 88888b.   .d88b.  888d888      'Y888b.    "
             "8888b.  888 888  888  8888b.    8888 888 88888b.  .d8888b ");
    mvprintw(04, ini_x_saiyadin,
             "    'Y88b. 888  888 888 '88b d8P  Y8b 888P'           'Y88b.     "
             "'88b 888 888  888     '88b   '888 888 888 '88b 88K     ");
    mvprintw(05, ini_x_saiyadin,
             "      '888 888  888 888  888 88888888 888               '888 "
             ".d888888 888 888  888 .d888888    888 888 888  888 'Y8888b.");
    mvprintw(06, ini_x_saiyadin,
             "Y88b  d88P Y88b 888 888 d88P Y8b.     888         Y88b  d88P 888 "
             " 888 888 Y88b 888 888  888    888 888 888  888      X88");
    mvprintw(07, ini_x_saiyadin,
             " 'Y8888P'   'Y88888 88888P'   'Y8888  888          'Y8888P'  "
             "'Y888888 888  'Y88888 'Y888888    888 888 888  888  88888P'");
    mvprintw(8, ini_x_saiyadin,
             "                    888                                          "
             "              888             888                      ");
    mvprintw(9, ini_x_saiyadin,
             "                    888                                          "
             "         Y8b d88P            d88P                      ");
    mvprintw(10, ini_x_saiyadin,
             "                    888                                          "
             "          'Y88P'           888P'                       ");
    mvprintw(13, ini_x_saiyadin,
             "   Os Saiyajins são uma raça alienígena super poderosa e formada "
             "para guerra, sua maior força vem no seu momento de maior");
    mvprintw(14, ini_x_saiyadin,
             "fraqueza, quando estão a beira de sua morte, quando ativam um "
             "estado chamado Super Saiyajin, em que sua aparência se    ");
    mvprintw(15, ini_x_saiyadin,
             "modfica, seu cabelo muda de cor, e sua força vital aumenta assim "
             "como seu ataque.                                       ");
    mvprintw(17, ini_x_saiyadin,
             "   Um grupo de Sayajins decidiram se unir e formar um grupo de "
             "luta, onde o objetivo (bem psicopata se parar pra pensar)");
    mvprintw(18, ini_x_saiyadin,
             "é lutarem entre si, e levarem um ao outro perto o suficiente da "
             "morte para ativar o estado Super Saiyajin, sem os riscos");
    mvprintw(19, ini_x_saiyadin,
             " de morrer, e depois se recuperarem em uma enfermaria, mantendo "
             "o aumento de força e energia vital. O objetivo de todos ");
    mvprintw(20, ini_x_saiyadin,
             "os Sayajins é de atigirem mais de 8000 pontos de energia vital, "
             "mas garantindo que sempre que um membro fique machucado ");
    mvprintw(21, ini_x_saiyadin,
             "haja um leito disponível para ele na Enfermaria.");
    mvprintw(23, ini_x_name, "by Rodrigo de Araujo Sacerdote");
    mvprintw(24, ini_x_name, "   Leonardo Kenji Kobaicy");
    mvprintw(25, ini_x_name, "   Enrique Antonio Ponce Cruz");
    mvprintw(26, ini_x_name, "   Ian Loron de Almeida");
    mvprintw(29, ini_x_name, "PRESS ENTER TO CONTINUE");
    refresh();
    while (getch() != 10) {
    }
    clear();
    return;
}

void drawInicial(int n_leitos, int n_lutadores) {
    // altura e largura da tela - usado para desenhar as arenas de acordo
    // com as especificacoes da tela do usuário.
    int scr_height, scr_width, margin_y = 0, margin_x = 2;

    // find sizes screen
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    scr_height = w.ws_row;
    scr_width = w.ws_col;

    ui height_enf, width_enf, begin_y_enf, begin_x_enf;
    ui height_lut, width_lut, begin_y_lut, begin_x_lut;
    ui height_qg, width_qg, begin_y_qg, begin_x_qg;

    height_enf = height_lut = ((scr_height - margin_y) / 2);
    width_enf = width_lut = width_qg = ((scr_width - margin_x) / 2);
    height_qg = (height_enf + height_lut + margin_y);

    begin_y_enf = begin_y_qg = 0;
    begin_x_enf = begin_x_lut = 0;
    begin_y_lut = begin_y_enf + height_enf + margin_y;
    begin_x_qg = begin_x_enf + width_enf + margin_x;

    // criação da enfermaria
    WINDOW* enfermaria =
        newwin(height_enf, width_enf, begin_y_enf, begin_x_enf);
    refresh();
    box(enfermaria, 0, 0);
    mvwprintw(enfermaria, 0, width_enf / 2 - 4, "ENFERMARIA");
    wrefresh(enfermaria);

    // desenhar os leitos inicialmente
    desenhaLeito(enfermaria, n_leitos);

    // criação do ringue
    WINDOW* ringue = newwin(height_lut, width_lut, begin_y_lut, begin_x_lut);
    refresh();
    box(ringue, 0, 0);
    mvwprintw(ringue, 0, width_lut / 2 - 3, "RINGUE");
    wrefresh(ringue);
    desenhaLutadores(ringue, n_lutadores);

    // criação do quadro geral
    WINDOW* quadroG = newwin(height_qg, width_qg, begin_y_qg, begin_x_qg);
    refresh();
    box(quadroG, 0, 0);
    mvwprintw(quadroG, 0, begin_x_qg / 2 - 12, "ESTADO DE CADA LUTADOR");
    wrefresh(quadroG);
    return;
}

int frontend() {
    initscr();  // inicializa a tela
    cbreak();   // permite c break (apertar control+c para fechar a aplicação)
    noecho();   // faz com que as teclas pressionadas não apareçam no terminal
    intro();
    start_color();
    if (!has_colors()) {
        printw("TERMINAL DOES NOT SUPPORT COLORS");
        getch();
        return -1;
    } else {
        init_pair(1, COLOR_WHITE, A_NORMAL);
        init_pair(2, COLOR_YELLOW, A_NORMAL);
        init_pair(3, COLOR_WHITE, COLOR_RED);
        init_pair(4, COLOR_GREEN, COLOR_WHITE);
        init_pair(5, COLOR_BLUE, A_NORMAL);
    }

    int n_leitos = 4;      // get_leitos();
    int n_lutadores = 10;  // get_lutadores();

    drawInicial(n_leitos,
                n_lutadores);  // desenhar as telas principais e iniciass
    /*
    while (1){
        //ativar funções para coletar valores de forma bonitinha
    }
    */
    while (getch() != 27) {
    }
    endwin();  // fecha a tela
    return 1;
}