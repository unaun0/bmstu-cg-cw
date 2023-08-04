from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QMessageBox

from uiKit.mainwindow import Ui_MainWindow


class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self): 
        super(MainWindow, self).__init__()
        self.setupUi(self)
        self.bindActions()
        self.bindButtons()

    def bindActions(self):
        pass

    def bindButtons(self):
        pass

    def closeMainWindow(self):
        buttonReply = QMessageBox.question(self, 'Завершение работы', 
                                           "Вы хотите завершить программу?", 
                                           QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if buttonReply == QMessageBox.Yes:
            QtWidgets.QApplication.quit()

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_0:
            pass
        elif event.key() == Qt.Key_Plus or event.key() == Qt.Key_Equal:
            pass
        elif event.key() == Qt.Key_Minus:
            pass
        elif event.key() == Qt.Key_Escape:
            pass
        elif event.key() == Qt.Key_Q:
            pass
        elif event.key() == Qt.Key_B:
            pass

    def closeEvent(self, event):
        self.closeMainWindow()
