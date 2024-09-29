/*
 * visual.cpp
 *
 *  Created on: 29.09.2024
 *      Author: Alx
 *
*/

#include <QDebug>

	#include "visual.h"

visual::visual(char* fullpath) {
#ifdef MARKERS
qDebug() << "visual::visual(QWidget *parent, char* fullpath) : QDialog(parent) { --- works";
#endif
ui.setupUi(this);
show();
#ifdef MARKERS
qDebug() << " *********************** constr over *************************** ";
#endif
} ///constr
