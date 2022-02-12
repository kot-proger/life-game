#ifndef _LABEL_H_
#define _LABEL_H_

#include <QtGui/QMouseEvent>
#include <QLabel>

class QExLabel : public QLabel
{
		Q_OBJECT
	public:
		QExLabel(QWidget *parent = 0);
	signals:
		void clicked();	
	protected:
		void mouseReleaseEvent(QMouseEvent *e);
		
};
#endif // !_LABEL_H_
