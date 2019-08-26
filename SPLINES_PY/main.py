import sys
from PyQt5.QtWidgets import QMainWindow, QApplication, QGraphicsScene
from PyQt5 import uic, QtGui, QtCore
import math
from numpy import arange

#return xx


def getSplineBezier(data):
    data.sort()
    result = []
    n = len(data)
    p = len(data) - 1

    for t in arange(0, 1, 0.01):
        x = 0
        y = 0

        for i in range(n):
            J = math.factorial(p)
            J = J / (math.factorial(p - i) * math.factorial(i))
            J = J * math.pow(t, i) * math.pow(1 - t, p - i)
            x = x + data[i][0] * J
            y = y + data[i][1] * J

        result.append([x, y])

    return result


Ui_MainWindow, QtBaseClass = uic.loadUiType("view\design.ui")

class MyApp(QMainWindow):
    def __init__(self):
        super(MyApp, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        #BUTTONS
        self.ui.addBtn.clicked.connect(self.addButton)
        self.ui.deleteBtn.clicked.connect(self.deleteButton)
        self.ui.calcBtn.clicked.connect(self.calc)

        #TABLE
        self.table = self.ui.table

        #DRAWING AREA
        self.drArea = self.ui.drawArea
        self.drArea.setAlignment(QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)
        self.drArea.setSceneRect(0, 0, self.drArea.viewport().width(), self.drArea.viewport().height())
        self.scene = QGraphicsScene()
        self.drArea.setScene(self.scene)

    def addButton(self):
        self.table.insertRow(self.ui.table.rowCount())

    def deleteButton(self):
        if self.table.rowCount() > 3:
            self.table.removeRow(self.table.rowCount() - 1)

    def calc(self):
        data = self.getDataFromTable()
        if data is None:
            return

        spline = getSplineBezier(data)

        self.scene.clear()
        self.drawLines(spline)
        self.drawDots(data)


    def drawLines(self, data):
        for i in range(len(data) - 1):
            self.scene.addLine(QtCore.QLineF(data[i][0], data[i][1],\
                                             data[i + 1][0], data[i + 1][1]))

    def drawDots(self, data):
        for i in range(len(data)):
            self.scene.addEllipse(QtCore.QRectF(data[i][0] - 5, data[i][1] - 5,
                                                10, 10))

    def getDataFromTable(self):
        for i in range(self.table.rowCount()):
            if self.table.item(i, 0) is None or self.table.item(i, 1) is None:
                return
            if self.table.item(i, 0).text() is "" or self.table.item(i, 1).text() is "":
                return

        data = []
        for i in range(self.table.rowCount()):
            x = float(self.table.item(i, 0).text())
            y = float(self.table.item(i, 1).text())
            data.append([x, y])

        return data



if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())
