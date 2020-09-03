//
// Created by ivankeks on 02.12.2019.
//

#include "Mail.h"

void lab9()
{
    Post *post = creatPost("Щелково Пацанская 13 14 1488");

    addMail(post, 14, 14888, "Щелково Анимечная 25 77 1488");
    addMail(post, 15, 14156, "Щелково Аыаы 43 22 1488");
    addMail(post, 16, 1986, "Щелково Анимечная 52 23 1488");
    addMail(post, 17, 346346, "Щелково Анимечная 52 25 1488");
    addMail(post, 18, 347347, "Щелково ВВВВВВ 12 72 1488");
    addMail(post, 19, 7347347, "Щелково Анимечная 25 75 1488");
    addMail(post, 23, 345534, "Щелково Анимечная 25 77 1488");
    addMail(post, 521, 1488, "Щелково ТоЧтоНужно 14 88 1488");
    addMail(post, 12, 23523, "Щелково Анимечная 25 77 1488");

    printMail(post, 1488);
    deleteMail(post, 1488);
    printMail(post, 1488);
    killPost(post);
}