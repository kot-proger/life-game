#include "label.h"

QExLabel::QExLabel(QWidget *parent) : QLabel(parent)
{	
}
void QExLabel::mouseReleaseEvent(QMouseEvent *e)
{
	
		if(e->button() == Qt::LeftButton)
		{
			emit clicked();
		}

	
}
