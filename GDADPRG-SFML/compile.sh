g++ GD_BaseEngine.cpp GD_AtlasParserM.cpp GD_GameResource.cpp  \
    GD_GameObject.cpp ACO_Background.cpp  GD_TextObject.cpp \
    GD_2DBlockObject.cpp GD_Trn.cpp  \
    GD_Component.cpp GD_ModularObject.cpp \
    ACO_BulletMovementComp.cpp ACO_ChargeComp.cpp ACO_ColliderComp.cpp \
    GD_PoolableComp.cpp ACO_TimedLifeComp.cpp \
    ACO_BulletObject.cpp ACO_BulletPool.cpp \
    ACO_EnemyAIComp.cpp ACO_CharHealthComp.cpp ACO_GameCharFactory.cpp \
    GD_ScenedGameEngine.cpp GD_Scene.cpp GD_SceneManager.cpp ACO_GameData.cpp \
    AC8_scene.cpp -o run.exe \
    -I/home/eteacher/lib_env/SFML-3.0.0/include/ \
    -L/home/eteacher/lib_env/SFML-3.0.0/build/lib/ \
    -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfreetype \
    -lpthread -ldl -lrt -lX11 -lXrandr -lXext -lXi -lXcursor -ludev

./run.exe
