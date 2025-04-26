QT       += core gui websockets xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = MSC
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += Communication
INCLUDEPATH += Components
INCLUDEPATH += Interface

SOURCES += \
    Communication/communicationchannel.cpp \
    Communication/websocketclient.cpp \
    Components/abilityfactoryclass.cpp \
    Components/agent1.cpp \
    Components/agent2.cpp \
    Components/agent3.cpp \
    Components/agent4.cpp \
    Components/agentfactoryclass.cpp \
    Components/bullet1.cpp \
    Components/bullet2.cpp \
    Components/bulletfactoryclass.cpp \
    Components/doublespeedability.cpp \
    Components/fullangleeyeability.cpp \
    Components/gun1.cpp \
    Components/gun2.cpp \
    Components/gunfactoryclass.cpp \
    Components/map1.cpp \
    Components/map2.cpp \
    Components/mapfactoryclass.cpp \
    Components/rangeradiusability.cpp \
    Components/realplayer.cpp \
    Components/teleportability.cpp \
    Interface/abilityinterface.cpp \
    Interface/agentinterface.cpp \
    Interface/bulletinterface.cpp \
    Interface/gameplayerinterface.cpp \
    Interface/guninterface.cpp \
    Interface/mapinterface.cpp \
    agentselectionpage.cpp \
    collisiondetectionclass.cpp \
    connecttoserverpage.cpp \
    datastore.cpp \
    Components/gameplayer.cpp \
    gamescene.cpp \
    gameview.cpp \
    itemstorepage.cpp \
    loginpage.cpp \
    main.cpp \
    maingamepage.cpp \
    mainwindow.cpp \
    middleware.cpp \
    Interface/playerinterface.cpp \
    processthreadclass.cpp \
    signuppage.cpp \
    specialutils.cpp \
    waitingpage.cpp

HEADERS += \
    Communication/communicationchannel.h \
    Communication/websocketclient.h \
    Components/abilityfactoryclass.h \
    Components/agent1.h \
    Components/agent2.h \
    Components/agent3.h \
    Components/agent4.h \
    Components/agentfactoryclass.h \
    Components/bullet1.h \
    Components/bullet2.h \
    Components/bulletfactoryclass.h \
    Components/doublespeedability.h \
    Components/fullangleeyeability.h \
    Components/gun1.h \
    Components/gun2.h \
    Components/gunfactoryclass.h \
    Components/map1.h \
    Components/map2.h \
    Components/mapfactoryclass.h \
    Components/rangeradiusability.h \
    Components/realplayer.h \
    Components/teleportability.h \
    GlobalConstant.h \
    Interface/abilityinterface.h \
    Interface/agentinterface.h \
    Interface/bulletinterface.h \
    Interface/gameplayerinterface.h \
    Interface/guninterface.h \
    Interface/mapinterface.h \
    agentselectionpage.h \
    collisiondetectionclass.h \
    connecttoserverpage.h \
    datastore.h \
    Components/gameplayer.h \
    gamescene.h \
    gameview.h \
    itemstorepage.h \
    loginpage.h \
    maingamepage.h \
    mainwindow.h \
    messages.h \
    middleware.h \
    Interface/playerinterface.h \
    processthreadclass.h \
    signuppage.h \
    specialutils.h \
    structures.h \
    waitingpage.h

FORMS += \
    agentselectionpage.ui \
    connecttoserverpage.ui \
    itemstorepage.ui \
    loginpage.ui \
    maingamepage.ui \
    mainwindow.ui \
    signuppage.ui \
    waitingpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
