#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QLabel>
#include <QPixmap>
#include <QCursor>
#include <QHBoxLayout>
#include <QWidget>
#include <QResizeEvent>
#include <QFrame>

#if defined(__aarch64__) || defined(__arm__)
    // Yocto embedded target
	#define FILE_PATH "/etc/"
#else
    // Ubuntu PC
    	#define FILE_PATH "/home/regan/Projects/yocto/meta-custom/recipes-apps/myapps/files/"
#endif


class SquareImageWidget : public QLabel
{
public:
    explicit SquareImageWidget(QWidget *parent = nullptr)
        : QLabel(parent)
    {
        setAlignment(Qt::AlignCenter);
        setFrameShape(QFrame::Box);
        setStyleSheet("background-color: grey;");
    }

    void setImage(const QString &path)
    {
    	original.load(path);

    	if (original.isNull()) {
        	qWarning("Cannot load image: %s", qPrintable(path));
        	return;
    	}

    	updateImage();
    }


/*protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QLabel::resizeEvent(event);
        updateImage();
    }
*/
private:
    void updateImage()
    {
        if (!original.isNull()) {
            int size = qMin(width(), height());

            QPixmap scaled = original.scaled(
                size,
                size
                //Qt::KeepAspectRatio,
                //Qt::SmoothTransformation
            );

            setPixmap(scaled);
        }
    }

    QPixmap original;
};


class MainWindow : public QMainWindow
{
public:
    MainWindow()
    {
        setWindowTitle("Qt Image Test");
        resize(1200, 700);

        //
        // Very thick toolbar
        //
        QToolBar *toolbar = new QToolBar(this);
        toolbar->setMovable(false);
        toolbar->setFixedHeight(50);   // thick

        toolbar->setStyleSheet(
            "QToolBar {"
            "  spacing: 20px;"
            "  background: #a0a0a0;"
            "}"
            "QToolButton {"
            "  font-size: 32px;"
            "  padding: 15px;"
            "}"
        );

        toolbar->addAction("HOME");
        toolbar->addAction("SETTINGS");
        QAction *exitAction = toolbar->addAction("EXIT");

        connect(exitAction, &QAction::triggered,
             qApp, &QApplication::quit);

        addToolBar(Qt::TopToolBarArea, toolbar);


        //
        // Main content
        //
        QWidget *central = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(central);

        //
        // Left side placeholder
        //
        QLabel *left = new QLabel("Application Area");
        left->setAlignment(Qt::AlignCenter);
        left->setStyleSheet(
            "font-size: 32px;"
            "background:#aaaaaa;"
        );


        //
        // Right square image
        //
        SquareImageWidget *image = new SquareImageWidget;

        image->setMinimumSize(300,300);

        // Change this to your image
	QString path = FILE_PATH "pinguin.jpeg";
        image->setImage(path);


        layout->addWidget(left, 1);
        layout->addWidget(image, 0);


        setCentralWidget(central);
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap cursorImage(":/images/mycursor.png");

    QCursor cursor(cursorImage, 0, 0);

    QApplication::setOverrideCursor(cursor);
    MainWindow window;
    window.show();

    return app.exec();
}

