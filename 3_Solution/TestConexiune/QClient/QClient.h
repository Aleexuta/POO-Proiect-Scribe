#pragma once

//#include <QtWidgets/QMainWindow>
#include <nlohmann/json.hpp>
#include <qmainwindow.h>
#include "ui_QClient.h"
#include <olc_net.h>
#include "IUser.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <qmessagebox.h>
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qprintdialog.h>
#include <QtPrintSupport/qprinterinfo.h>
#include <QCloseEvent>
#include "Find_Form.h"
#include "Replace_Form.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QCloseEvent>
#include "Table_Dialog.h"
class TreeModel;
class TreeItem;
enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerAcceptRegister,
    ServerDenyRegister,
    ServerAcceptLogin,
    ServerDenyLogin,
    ServerDeny,
	ServerRegister,
    ServerLogin,
    NewNode,
    NewNodeAccept,
    NewNodeDeny,
    LoadAllNodes,
    LoadAllNodesAccept,
    RemoveNode,
    SaveNode
};


class QClient : public QMainWindow, public olc::net::client_interface<CustomMsgTypes>
{
    Q_OBJECT

private:
    static QClient* instance;
     QClient(QWidget *parent = Q_NULLPTR);
    ~QClient();
    void closeEvent(QCloseEvent *event)override;
    void checkSave(bool &cancel);
    void save();
    void newFile();
    void openFile();
private:
    Ui::QClientClass ui;
    IUser* user;
    QString m_path;
    bool m_changed;
    TreeModel* model;
    QVector<QCheckBox *> m_checkboxes;
public:
    static QClient* getInstance();
    void deleteInstance();
    void IncomingMessages();

    void sendRegisterMessage(std::string j);
    void sendLoginMessage(std::string j);
    void sendNewNodeMessage(std::string j);
    void sendRemoveNodeMessage(std::string j);

    void setUserInfo(std::string mesaj);
    void setGuestInfo();
    void setNodeId(int id);

    TreeItem* getRootItem();
    int  getNumberOfNodes();
    void incrementNumberOfNodes();
    void decrementNumberOfNodes();
    void add_corresponding_checkboxes();
    void save_type_checkboxes();
private:
    auto makeJsonNewNode(std::string name, int iduser, int idparent, int idnode, std::string namephoto = "");
    void sendLoadAllNodesMessage(std::string id);
    void LoadAllNodes(std::string j);
    void LoadChildren(TreeItem * root,nlohmann::basic_json<> js, int &pos);
    void prepareChildToInsert(TreeItem* root, nlohmann::basic_json<> js, int pos);
public:
    void insertNewNode(const std::string photo,const std::string name);
    void inservNewSubnode(const std::string photo,const std::string name);
    void updateActions();
    void deleteNode();
    void OpenNote();
public slots:
    
    void on_actionAdd_New_Node_triggered();
    void on_actionAdd_New_Subnode_triggered();
    void on_actionDelete_Node_triggered();
    void on_actionOpen_Note_triggered();

private slots:
    
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionPrint_triggered();
    void on_actionExit_triggered();
    void on_actionSave_triggered();
    void on_actionCopy_triggered();
    void on_textEdit_textChanged();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionZoom_in_triggered();
    void on_actionZoom_out_triggered();
    void on_actionSelect_All_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionBold_triggered();
    void on_actionItalic_triggered();
    void on_actionStrikeout_triggered();
    void on_actionUnderline_triggered();
    void on_actionColor_triggered();
    void on_actionFont_triggered();
    void on_actionAlign_Left_triggered();
    void on_actionAlign_Right_triggered();
    void on_actionAlign_Center_triggered();
    void on_action_Insert_List_triggered();
    void on_actionInsert_Table_triggered();
    void on_actionAdd_Column_triggered();
    void on_actionAdd_Row_triggered();
    void on_actionInsert_Image_triggered();
    void on_actionInsert_Checkbox_triggered();
};

//ceva