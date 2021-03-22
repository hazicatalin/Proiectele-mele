"""Jocul Minesweeper

Programul permite utilizatorului sa deschida o interfata
a jocului minesweeper creata utilizand pygame, joc care ulterior
poate fi jucat de catre acesta.

Initial pe ecran va aparea o fereastra cu patru casute pentru
a introduce, pe rand, dimensiunile matricei(numarul de coloane,
numarul de linii), numarul de bombe aflate in aceasta si secundele
in care dorim sa terminam jocul. Numarul de linii si coloane nu
poat fi mai mari decat 29 sau mai mici decat 4, numarul de bombe
nu poate depasi numarul de linii inmultit cu numarul de coloane, iar
timpul nu poate fi mai mic decat 1 sau mai mare decat 1000.
In cazul in care numarul introdus nu este in intervalul specificat
sau sunt introduse alte caractere in afara de numere, jocul va cere
reintrooducerea unui numar.

Dupa introducerea tuturor numerelor cerute incepe jocul, aparand
o alta fereastra, de dimensiuni mai mari sau mai mici, in functie
de dimensiunile matricei.

Patrea de sus a ecranului este alcatuita dintr-un cronometru in partea
stanga, in centru un smiley face care atunci cand este selectat prin
click stanga reia jocul de la introducerea valorilor matricei, acelasi
lucru se poate intampla si prin apasarea tastei "F2", iar in partea din
dreapta va aparea initial numarul de bombe. Sub acestea se afla o
matrice formata din patratele goale care pot fi selectate pentru a
vedea ce se afla acolo, prin click stanga, sau pot fi marcate cu
stegulet prin apasarea unui click dreapta pe acestea, moment in care
numarul din partea dreapta sus scade cu 1, sau cu semnul intrebarii(?)
prin apasarea inca o data click dreapta peste stegulet. Pentru a trece
inapoi de la "?" la patratel gol mai apasam inca  o data click dreapta.
Patratelele marcate cu stegulet nu pot fi selectate pentru a afla ce se
ascunde sub aceasta.

In momentru in care timpul alocat pentru rezolvarea jocului expira pe
ecram va apara "YOU LOST" si smiley face va fi inlocuit cu un sad face
ce poate fi apasat pentru a reincepe jocul. Acelasi luctru se petrece si
la apasarea unei celule in care se afla o bomba, aici, in plus, vor
aparea pe ecran si toate bombele din matrice.

Jocul va fi castigat in momentul in care toate celulele ce nu contin
bombe vor fi afisate, moment in care pe ecran va aparea mesajul "YOU
WON", iar pentru a reincepe trebuie apasat pe smiley face.

Programul contine urmatoarele functii si proceduri:
    *end_game - returneaza 0 daca nu s-a sfarsit, 1 daca jucatorul a
                castigat
                si 2 daca jucatorul a pierdut
    *read_size - creeaza o fereastra in care se citesc dimensiunile
                 matricei, numarul de bombe si timpul, acestea fiind
                 salvate in variabilele
                 lines_number, columns_number, bombs_number,
                 time_minutes si time_seconds, salvate global
    *show_cells - ia coordonatele x si y ale matricei si pune 1 in
                  matricea show la adresa respectiva, luand si celulele
                  din jurul acesteia daca in matricea mat la aceeasi
                  pozitie se afla 0
    *play_game - in aceasta procedura se realizeaza jocul, se citesc
                 coordonatele in este apasat mouse-ul si se apeleaza
                 show_mat, sau se reincepe jocul
    *game_finished - procedura apelata cand este gata jocul si afiseaza
                     daca jucatorul a castigat sau pierdut
    *timer - actializeaza la fiecare secunda timer-ul jocului
    *show_matrix - decide ce imagine va afgisa pentru fiecare celula in
                   parte
    *create_matrix - creeaza matricile shoe si mat in functie de
                     valorile introduse, punand in matricea mat numarul
                     necesar de bombe random
    *main - procedura principala a jocului

"""
import pygame
import random
import sys
import numpy as np

sys.setrecursionlimit(9000)
mat = np.empty((35, 35))
show = np.empty((35, 35))
bombs_number = 0
columns_number = 0
lines_number = 0
marked_bombs = 0
shown_cells = 0
lost = False
time_minutes = 0
time_seconds = 0


def end_game():
    """Verifica daca jocul se termina si daca a fost castigat

        Parametrii
        ----------
        nu primeste niciun parametru

        Returneaza
        -------
        0
            jocul nu s-a terminat
        1
            jocul a fost castigat
        2
            jocul a fost pierdut

        """
    global shown_cells
    global columns_number
    global lines_number
    global bombs_number
    global lost

    if shown_cells == (columns_number*lines_number) - bombs_number:
        return 1
    if time_seconds == 0 and time_minutes == 0:
        return 2
    if lost:
        return 2
    return 0


def read_size():
    """Citeste dimensiunile matricei, numarul de bombe si numarul de
        secunde

        Parametrii
        ----------
        nu primeste niciun parametru
        citeste din fereastra 4 parametrii pe care ii salveaza in
        variabile globale

        Returneaza
        -------
        nu returneaza nimic

    """
    global columns_number
    global lines_number
    global bombs_number
    global marked_bombs
    global lost
    global time_seconds
    global time_minutes
    lost = False
    selected = 1
    user_text_1 = ''
    user_text_2 = ''
    user_text_3 = ''
    user_text_4 = ''

    base_font = pygame.font.Font(None, 30)
    screen2 = pygame.display.set_mode((300, 500))
    pygame.display.set_caption('MINESWEEPER')
    bg = pygame.image.load('images/background.png')
    input_rect_1 = pygame.Rect(100, 110, 100, 30)
    input_rect_4 = pygame.Rect(100, 210, 100, 30)
    input_rect_2 = pygame.Rect(100, 310, 100, 30)
    input_rect_3 = pygame.Rect(100, 410, 100, 30)
    text_1 = base_font.render('NUMBER OF COLUMNS:', True, (255, 0, 0))
    text_1_rect = text_1.get_rect(center=(150, 100))
    text_4 = base_font.render('NUMBER OF LINES:', True, (255, 0, 0))
    text_4_rect = text_4.get_rect(center=(150, 200))
    text_2 = base_font.render('NUMBER OF BOMBS:', True, (255, 0, 0))
    text_2_rect = text_2.get_rect(center=(150, 300))
    text_3 = base_font.render('NUMBER OF SECONDS:', True, (255, 0, 0))
    text_3_rect = text_3.get_rect(center=(150, 400))
    color_1 = (0, 150, 150)
    color_2 = (0, 0, 0)
    color_3 = (0, 0, 0)
    color_4 = (0, 0, 0)
    while True:
        screen2.blit(bg, (0, 0))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN and selected == 4:
                if event.key == pygame.K_BACKSPACE:
                    user_text_3 = user_text_3[:-1]
                elif event.unicode == '':
                    if user_text_3.isnumeric():
                        time = int(user_text_3)
                        if 0 < time <= 1000:
                            time_minutes = int(time / 60)
                            time_seconds = time - (60 * time_minutes)
                            selected = 5
                        else:
                            user_text_3 = ''
                    else:
                        user_text_3 = ''
                else:
                    user_text_3 += event.unicode
            if event.type == pygame.KEYDOWN and selected == 3:
                if event.key == pygame.K_BACKSPACE:
                    user_text_2 = user_text_2[:-1]
                elif event.unicode == '':
                    if user_text_2.isnumeric():
                        bombs_number = int(user_text_2)
                        if (0 < bombs_number <=
                                (columns_number * lines_number)):
                            marked_bombs = bombs_number
                            selected = 4
                            color_2 = (0, 0, 0)
                            color_3 = (0, 150, 150)
                        else:
                            user_text_2 = ''
                    else:
                        user_text_2 = ''
                else:
                    user_text_2 += event.unicode
            if event.type == pygame.KEYDOWN and selected == 2:
                if event.key == pygame.K_BACKSPACE:
                    user_text_4 = user_text_4[:-1]
                elif event.unicode == '':
                    if user_text_4.isnumeric():
                        lines_number = int(user_text_4)
                        if 3 < lines_number < 30:
                            marked_bombs = bombs_number
                            selected = 3
                            color_4 = (0, 0, 0)
                            color_2 = (0, 150, 150)
                        else:
                            user_text_4 = ''
                    else:
                        user_text_4 = ''
                else:
                    user_text_4 += event.unicode
            if event.type == pygame.KEYDOWN and selected == 1:
                if event.key == pygame.K_BACKSPACE:
                    user_text_1 = user_text_1[:-1]
                elif event.unicode == '':
                    if user_text_1.isnumeric():
                        columns_number = int(user_text_1)
                        if 3 < columns_number < 30:
                            selected = 2
                            color_1 = (0, 0, 0)
                            color_4 = (0, 150, 150)
                        else:
                            user_text_1 = ''
                    else:
                        user_text_1 = ''
                else:
                    user_text_1 += event.unicode
            if selected == 5:
                create_matrix()
                play_game()
                pygame.quit()
                sys.exit()
        screen2.blit(text_1, text_1_rect)
        screen2.blit(text_2, text_2_rect)
        screen2.blit(text_3, text_3_rect)
        screen2.blit(text_4, text_4_rect)
        pygame.draw.rect(screen2, color_1, input_rect_1)
        pygame.draw.rect(screen2, color_2, input_rect_2)
        pygame.draw.rect(screen2, color_3, input_rect_3)
        pygame.draw.rect(screen2, color_4, input_rect_4)
        text_surface_1 = base_font.render(user_text_1, True,
                                          (255, 255, 255))
        screen2.blit(text_surface_1, (100, 115))
        text_surface_1 = base_font.render(user_text_4, True,
                                          (255, 255, 255))
        screen2.blit(text_surface_1, (100, 215))
        text_surface_1 = base_font.render(user_text_2, True,
                                          (255, 255, 255))
        screen2.blit(text_surface_1, (100, 315))
        text_surface_1 = base_font.render(user_text_3, True,
                                          (255, 255, 255))
        screen2.blit(text_surface_1, (100, 415))
        pygame.display.update()


def show_cells(x, y):
    """Pune in matricea de afisare show 1 pentru ca celula respectiva
    sa apara in fereastgra

        Parametrii
        ----------
        x: int
            coordonata liniei matricei
        y : int
            coordonata coloanei matricei

        Returneaza
        -------
        nu returneaza nimic

    """
    global mat
    global shown_cells
    global show
    global columns_number
    global lines_number
    global lost
    if show[x][y] == 0 or show[x][y] == 3:
        shown_cells += 1
        show[x][y] = 1
        if mat[x][y] == -1:
            lost = True
            for i in range(columns_number+1):
                for j in range(lines_number+1):
                    if mat[i][j] == -1:
                        show[i][j] = 1
            shown_cells = columns_number*lines_number
        elif mat[x][y] == 0:
            if x > 1:
                show_cells(x-1, y)
                if y > 1:
                    show_cells(x-1, y-1)
                if y < lines_number - 1:
                    show_cells(x-1, y+1)
            if x < columns_number:
                show_cells(x+1, y)
                if y > 1:
                    show_cells(x+1, y-1)
                if y < lines_number:
                    show_cells(x+1, y+1)
            if y > 1:
                show_cells(x, y - 1)
            if y < lines_number - 1:
                show_cells(x, y + 1)


def play_game():
    """Procedura in care se realizeaza jocul, ce ruleaza pana la
    terminarea acestuia

        Parametrii
        ----------
        nu are parametrii

        Returneaza
        -------
        nu returneaza nimic

    """
    global marked_bombs
    global time_seconds
    global time_minutes
    screen = pygame.display.set_mode((columns_number * 32+64,
                                      lines_number * 32 + 114))
    smiley = pygame.image.load('images/smiley.png')
    smiley = pygame.transform.scale(smiley, (40, 40))
    pygame.display.set_caption('MINESWEEPER')
    bg = pygame.image.load('images/background.png')
    bg = pygame.transform.scale(bg, (1200, 1200))
    clock = pygame.time.Clock()
    start = 0
    while True:
        screen.blit(bg, (0, 0))
        screen.blit(smiley, ((columns_number * 32+64)/2-20, 30))
        timer(time_minutes, time_seconds, screen)
        show_matrix(screen)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if (event.type == pygame.KEYDOWN
                    and event.key == pygame.K_F2):
                read_size()
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONUP:
                pos = pygame.mouse.get_pos()
                if ((columns_number * 32+64)/2-20 < pos[0]
                        < (columns_number * 32+64)/2+20
                        and 30 < pos[1] < 70):
                    read_size()
                    pygame.quit()
                    sys.exit()
                if (32 < pos[0] < columns_number * 32 + 32 and 82
                        < pos[1] < lines_number * 32 + 114):
                    x = int(pos[0]/32)
                    y = int((pos[1]-50)/32)
                    print(str(x) + ";" + str(y))
                    if x <= columns_number and y <= lines_number:
                        if (event.button == 1 and (show[x][y] == 0
                                                   or show[x][y] == 3)):
                            show_cells(x, y)
                        elif event.button == 3 and show[x][y] == 0:
                            show[x][y] = 2
                            marked_bombs -= 1
                        elif event.button == 3 and show[x][y] == 2:
                            show[x][y] = 3
                            marked_bombs += 1
                        elif event.button == 3 and show[x][y] == 3:
                            show[x][y] = 0
        pygame.display.update()
        if end_game() == 1 or end_game() == 2:
            game_finished(time_minutes, time_seconds, screen)
        start += 1
        if start == 10:
            time_seconds -= 1
            start = 0
        if time_seconds == -1:
            start = 0
            time_seconds = 59
            time_minutes -= 1
        clock.tick(10)


def game_finished(
        minutes, seconds, screen):
    """Afiseaza in fereastra jocului daca ai castigat sau pierdut,
    asteptand reinceperea jocului

        Parametrii
        ----------
        minutes: int
            minutele la terminarea jocului
        seconds : int
            secundele la terminarea jocului
        screen : pygame.dysplay
            ecranul jocului

        Returneaza
        -------
        nu returneaza nimic

    """
    global columns_number
    global lines_number
    bg = pygame.image.load('images/background.png')
    sad = pygame.image.load('images/sad.png')
    smiley = pygame.image.load('images/smiley.png')
    sad = pygame.transform.scale(sad, (40, 40))
    smiley = pygame.transform.scale(smiley, (40, 40))
    game_font = pygame.font.Font(None, 50)
    screen.blit(bg, (0, 0))
    show_matrix(screen)
    while True:
        timer(minutes, seconds, screen)

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if (event.type == pygame.KEYDOWN
                    and event.key == pygame.K_F2):
                read_size()
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONUP:
                pos = pygame.mouse.get_pos()
                if ((columns_number * 32+64)/2-20 < pos[0]
                        < (columns_number * 32+64)/2+20
                        and 30 < pos[1] < 70):
                    read_size()
                    pygame.quit()
                    sys.exit()
        if end_game() == 1:
            screen.blit(smiley, ((columns_number * 32+64)/2-20, 30))
            end_surface = game_font.render('YOU WON!!!', True,
                                           (255, 0, 0))
            end_rect = end_surface.get_rect(
                center=((columns_number * 32 + 64) / 2,
                        (lines_number * 32 + 64) / 2))
            screen.blit(end_surface, end_rect)
        if end_game() == 2:
            screen.blit(sad, ((columns_number * 32+64)/2-20, 30))
            end_surface = game_font.render('YOU LOST!!!', True,
                                           (255, 0, 0))
            end_rect = end_surface.get_rect(
                center=((columns_number * 32 + 64) / 2,
                        (lines_number * 32 + 64) / 2))
            screen.blit(end_surface, end_rect)
        pygame.display.update()


def timer(
        minutes, seconds,
        screen):
    """calculeaza minutele, secundele si le afiseaza in ecran

        Parametrii
        ----------
        minutes: int
            minutele la momentul respectiv
        seconds : int
            secundele la momentul respectiv
        screen : pygame.dysplay
            ecranul jocului

        Returneaza
        -------
        nu returneaza nimic

    """
    global marked_bombs
    global columns_number
    global lines_number
    game_font = pygame.font.Font(None, 50)
    timer_surface = game_font.render(str(minutes) + ":" + str(seconds),
                                     True, (255, 0, 0))
    timer_rect = timer_surface.get_rect(
        center=((columns_number * 32 + 64) / 4, 50))
    score_surface = game_font.render(str(marked_bombs), True,
                                     (255, 0, 0))
    score_rect = score_surface.get_rect(
        center=((columns_number * 32 + 64) * 3 / 4, 50))
    screen.blit(timer_surface, timer_rect)
    screen.blit(score_surface, score_rect)


def show_matrix(screen):

    """Afiseaza in fereastra matricea (utilizant poze)

        Parametrii
        ----------
        screen : pygame.dysplay
            ecranul jocului

        Returneaza
        -------
        nu returneaza nimic

    """
    global mat
    global show
    ds = pygame.transform.scale2x(
        pygame.image.load('images/Default.png'))
    mine = pygame.transform.scale2x(
        pygame.image.load('images/Mine.png'))
    flag = pygame.transform.scale2x(
        pygame.image.load('images/flag.png'))
    flag = pygame.transform.scale(flag, (32, 32))
    unknown = pygame.transform.scale2x(
        pygame.image.load('images/unknown.png'))
    e0 = pygame.transform.scale2x(
        pygame.image.load('images/Empty0.png'))
    e1 = pygame.transform.scale2x(
        pygame.image.load('images/Empty1.png'))
    e2 = pygame.transform.scale2x(
        pygame.image.load('images/Empty2.png'))
    e3 = pygame.transform.scale2x(
        pygame.image.load('images/Empty3.png'))
    e4 = pygame.transform.scale2x(
        pygame.image.load('images/Empty4.png'))
    e5 = pygame.transform.scale2x(
        pygame.image.load('images/Empty5.png'))
    e6 = pygame.transform.scale2x(
        pygame.image.load('images/Empty6.png'))
    e7 = pygame.transform.scale2x(
        pygame.image.load('images/Empty7.png'))
    e8 = pygame.transform.scale2x(
        pygame.image.load('images/Empty8.png'))
    for i in range(1, columns_number+1):
        for j in range(1, lines_number+1):
            if show[i][j] == 1:
                if mat[i][j] == -1:
                    screen.blit(mine, (i * 32, j * 32 + 50))
                if mat[i][j] == 0:
                    screen.blit(e0, (i * 32, j * 32 + 50))
                if mat[i][j] == 1:
                    screen.blit(e1, (i * 32, j * 32 + 50))
                if mat[i][j] == 2:
                    screen.blit(e2, (i * 32, j * 32 + 50))
                if mat[i][j] == 3:
                    screen.blit(e3, (i * 32, j * 32 + 50))
                if mat[i][j] == 4:
                    screen.blit(e4, (i * 32, j * 32 + 50))
                if mat[i][j] == 5:
                    screen.blit(e5, (i * 32, j * 32 + 50))
                if mat[i][j] == 6:
                    screen.blit(e6, (i * 32, j * 32 + 50))
                if mat[i][j] == 7:
                    screen.blit(e7, (i * 32, j * 32 + 50))
                if mat[i][j] == 8:
                    screen.blit(e8, (i * 32, j * 32 + 50))
            elif show[i][j] == 0:
                screen.blit(ds, (i * 32, j * 32 + 50))
            elif show[i][j] == 2:
                screen.blit(flag, (i * 32, j * 32 + 50))
            elif show[i][j] == 3:
                screen.blit(unknown, (i * 32, j * 32 + 50))


def create_matrix():

    """creeaza matricea mat si show in functie de valorile introduse la
    inceput

        Parametrii
        ----------
        nu are parametrii

        Returneaza
        -------
        nu returneaza nimic

    """
    global columns_number
    global lines_number
    global bombs_number
    global mat
    global show
    for i in range(columns_number + 2):
        for j in range(lines_number + 2):
            mat[i][j] = 0
            show[i][j] = 0
    i = 0
    while i < bombs_number:
        x = random.randint(1, columns_number)
        y = random.randint(1, lines_number)
        if mat[x][y] == 0:
            mat[x][y] = -1
            i += 1

    for i in range(1, columns_number+1):
        for j in range(1, lines_number+1):
            if mat[i][j] == 0:
                if mat[i-1][j-1] == -1:
                    mat[i][j] += 1
                if mat[i-1][j] == -1:
                    mat[i][j] += 1
                if mat[i-1][j+1] == -1:
                    mat[i][j] += 1
                if mat[i][j-1] == -1:
                    mat[i][j] += 1
                if mat[i][j+1] == -1:
                    mat[i][j] += 1
                if mat[i+1][j-1] == -1:
                    mat[i][j] += 1
                if mat[i+1][j] == -1:
                    mat[i][j] += 1
                if mat[i+1][j+1] == -1:
                    mat[i][j] += 1


def main():
    pygame.init()
    read_size()


if __name__ == "__main__":

    main()
