/*
 * visual.h
 *
 *  Created on: 29.09.2024
 *      Author: Alx
 */

#ifndef VISU_H_
#define VISU_H_

#include <QDebug>
#include <QDialog>

	#include "ui_visual.h"

class visual : public QDialog {

    Q_OBJECT

public:

	 visual(char*);

	virtual ~visual() {}
	
	::Ui::visual ui;

public slots:

signals:

private:

private slots:

protected:

}; //class

#endif
