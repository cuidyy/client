/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_pushButtonLogin_clicked",
    "",
    "on_pushButtonRegister_clicked",
    "on_pushButtonSelectFile_clicked",
    "on_pushButtonUpload_clicked",
    "on_pushButtonFlush_clicked",
    "on_ListViewCloudDoubleClicked",
    "QModelIndex",
    "index",
    "on_ListViewCloudRightClicked",
    "on_pushButtonUploadFunction_clicked",
    "on_pushButtonCloudFunction_clicked",
    "on_pushButtonLogout_clicked",
    "on_pushButtonBackFromUpload_clicked",
    "on_pushButtonBackFromCloud_clicked",
    "on_pushButtonManageFunction_clicked",
    "on_pushButtonBackFromManage_clicked",
    "on_pushButtonDownload_clicked",
    "on_pushButtonDelete_clicked",
    "on_pushButtonShare_clicked",
    "on_pushButtonCancelShare_clicked",
    "on_pushButtonShareFunction_clicked",
    "on_pushButtonFlushShare_clicked",
    "on_pushButtonCollect_clicked",
    "on_pushButtonBackFromShare_clicked",
    "on_ListViewShareDoubleClicked",
    "on_pushButtonImageEditorFunction_clicked",
    "on_pushButtonBackFromEditor_clicked",
    "on_pushButtonOpenImage_clicked",
    "on_pushButtonSaveImage_clicked",
    "on_pushButtonRotateLeft_clicked",
    "on_pushButtonRotateRight_clicked",
    "on_pushButtonFlipH_clicked",
    "on_pushButtonFlipV_clicked",
    "on_pushButtonCrop_clicked",
    "on_pushButtonFilter_clicked",
    "on_pushButtonAdjust_clicked",
    "on_pushButtonReset_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[78];
    char stringdata0[11];
    char stringdata1[27];
    char stringdata2[1];
    char stringdata3[30];
    char stringdata4[32];
    char stringdata5[28];
    char stringdata6[27];
    char stringdata7[30];
    char stringdata8[12];
    char stringdata9[6];
    char stringdata10[29];
    char stringdata11[36];
    char stringdata12[35];
    char stringdata13[28];
    char stringdata14[36];
    char stringdata15[35];
    char stringdata16[36];
    char stringdata17[36];
    char stringdata18[30];
    char stringdata19[28];
    char stringdata20[27];
    char stringdata21[33];
    char stringdata22[35];
    char stringdata23[32];
    char stringdata24[29];
    char stringdata25[35];
    char stringdata26[30];
    char stringdata27[41];
    char stringdata28[36];
    char stringdata29[31];
    char stringdata30[31];
    char stringdata31[32];
    char stringdata32[33];
    char stringdata33[27];
    char stringdata34[27];
    char stringdata35[26];
    char stringdata36[28];
    char stringdata37[28];
    char stringdata38[27];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 26),  // "on_pushButtonLogin_clicked"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 29),  // "on_pushButtonRegister_clicked"
        QT_MOC_LITERAL(69, 31),  // "on_pushButtonSelectFile_clicked"
        QT_MOC_LITERAL(101, 27),  // "on_pushButtonUpload_clicked"
        QT_MOC_LITERAL(129, 26),  // "on_pushButtonFlush_clicked"
        QT_MOC_LITERAL(156, 29),  // "on_ListViewCloudDoubleClicked"
        QT_MOC_LITERAL(186, 11),  // "QModelIndex"
        QT_MOC_LITERAL(198, 5),  // "index"
        QT_MOC_LITERAL(204, 28),  // "on_ListViewCloudRightClicked"
        QT_MOC_LITERAL(233, 35),  // "on_pushButtonUploadFunction_c..."
        QT_MOC_LITERAL(269, 34),  // "on_pushButtonCloudFunction_cl..."
        QT_MOC_LITERAL(304, 27),  // "on_pushButtonLogout_clicked"
        QT_MOC_LITERAL(332, 35),  // "on_pushButtonBackFromUpload_c..."
        QT_MOC_LITERAL(368, 34),  // "on_pushButtonBackFromCloud_cl..."
        QT_MOC_LITERAL(403, 35),  // "on_pushButtonManageFunction_c..."
        QT_MOC_LITERAL(439, 35),  // "on_pushButtonBackFromManage_c..."
        QT_MOC_LITERAL(475, 29),  // "on_pushButtonDownload_clicked"
        QT_MOC_LITERAL(505, 27),  // "on_pushButtonDelete_clicked"
        QT_MOC_LITERAL(533, 26),  // "on_pushButtonShare_clicked"
        QT_MOC_LITERAL(560, 32),  // "on_pushButtonCancelShare_clicked"
        QT_MOC_LITERAL(593, 34),  // "on_pushButtonShareFunction_cl..."
        QT_MOC_LITERAL(628, 31),  // "on_pushButtonFlushShare_clicked"
        QT_MOC_LITERAL(660, 28),  // "on_pushButtonCollect_clicked"
        QT_MOC_LITERAL(689, 34),  // "on_pushButtonBackFromShare_cl..."
        QT_MOC_LITERAL(724, 29),  // "on_ListViewShareDoubleClicked"
        QT_MOC_LITERAL(754, 40),  // "on_pushButtonImageEditorFunct..."
        QT_MOC_LITERAL(795, 35),  // "on_pushButtonBackFromEditor_c..."
        QT_MOC_LITERAL(831, 30),  // "on_pushButtonOpenImage_clicked"
        QT_MOC_LITERAL(862, 30),  // "on_pushButtonSaveImage_clicked"
        QT_MOC_LITERAL(893, 31),  // "on_pushButtonRotateLeft_clicked"
        QT_MOC_LITERAL(925, 32),  // "on_pushButtonRotateRight_clicked"
        QT_MOC_LITERAL(958, 26),  // "on_pushButtonFlipH_clicked"
        QT_MOC_LITERAL(985, 26),  // "on_pushButtonFlipV_clicked"
        QT_MOC_LITERAL(1012, 25),  // "on_pushButtonCrop_clicked"
        QT_MOC_LITERAL(1038, 27),  // "on_pushButtonFilter_clicked"
        QT_MOC_LITERAL(1066, 27),  // "on_pushButtonAdjust_clicked"
        QT_MOC_LITERAL(1094, 26)   // "on_pushButtonReset_clicked"
    },
    "MainWindow",
    "on_pushButtonLogin_clicked",
    "",
    "on_pushButtonRegister_clicked",
    "on_pushButtonSelectFile_clicked",
    "on_pushButtonUpload_clicked",
    "on_pushButtonFlush_clicked",
    "on_ListViewCloudDoubleClicked",
    "QModelIndex",
    "index",
    "on_ListViewCloudRightClicked",
    "on_pushButtonUploadFunction_clicked",
    "on_pushButtonCloudFunction_clicked",
    "on_pushButtonLogout_clicked",
    "on_pushButtonBackFromUpload_clicked",
    "on_pushButtonBackFromCloud_clicked",
    "on_pushButtonManageFunction_clicked",
    "on_pushButtonBackFromManage_clicked",
    "on_pushButtonDownload_clicked",
    "on_pushButtonDelete_clicked",
    "on_pushButtonShare_clicked",
    "on_pushButtonCancelShare_clicked",
    "on_pushButtonShareFunction_clicked",
    "on_pushButtonFlushShare_clicked",
    "on_pushButtonCollect_clicked",
    "on_pushButtonBackFromShare_clicked",
    "on_ListViewShareDoubleClicked",
    "on_pushButtonImageEditorFunction_clicked",
    "on_pushButtonBackFromEditor_clicked",
    "on_pushButtonOpenImage_clicked",
    "on_pushButtonSaveImage_clicked",
    "on_pushButtonRotateLeft_clicked",
    "on_pushButtonRotateRight_clicked",
    "on_pushButtonFlipH_clicked",
    "on_pushButtonFlipV_clicked",
    "on_pushButtonCrop_clicked",
    "on_pushButtonFilter_clicked",
    "on_pushButtonAdjust_clicked",
    "on_pushButtonReset_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      35,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  224,    2, 0x08,    1 /* Private */,
       3,    0,  225,    2, 0x08,    2 /* Private */,
       4,    0,  226,    2, 0x08,    3 /* Private */,
       5,    0,  227,    2, 0x08,    4 /* Private */,
       6,    0,  228,    2, 0x08,    5 /* Private */,
       7,    1,  229,    2, 0x08,    6 /* Private */,
      10,    1,  232,    2, 0x08,    8 /* Private */,
      11,    0,  235,    2, 0x08,   10 /* Private */,
      12,    0,  236,    2, 0x08,   11 /* Private */,
      13,    0,  237,    2, 0x08,   12 /* Private */,
      14,    0,  238,    2, 0x08,   13 /* Private */,
      15,    0,  239,    2, 0x08,   14 /* Private */,
      16,    0,  240,    2, 0x08,   15 /* Private */,
      17,    0,  241,    2, 0x08,   16 /* Private */,
      18,    0,  242,    2, 0x08,   17 /* Private */,
      19,    0,  243,    2, 0x08,   18 /* Private */,
      20,    0,  244,    2, 0x08,   19 /* Private */,
      21,    0,  245,    2, 0x08,   20 /* Private */,
      22,    0,  246,    2, 0x08,   21 /* Private */,
      23,    0,  247,    2, 0x08,   22 /* Private */,
      24,    0,  248,    2, 0x08,   23 /* Private */,
      25,    0,  249,    2, 0x08,   24 /* Private */,
      26,    1,  250,    2, 0x08,   25 /* Private */,
      27,    0,  253,    2, 0x08,   27 /* Private */,
      28,    0,  254,    2, 0x08,   28 /* Private */,
      29,    0,  255,    2, 0x08,   29 /* Private */,
      30,    0,  256,    2, 0x08,   30 /* Private */,
      31,    0,  257,    2, 0x08,   31 /* Private */,
      32,    0,  258,    2, 0x08,   32 /* Private */,
      33,    0,  259,    2, 0x08,   33 /* Private */,
      34,    0,  260,    2, 0x08,   34 /* Private */,
      35,    0,  261,    2, 0x08,   35 /* Private */,
      36,    0,  262,    2, 0x08,   36 /* Private */,
      37,    0,  263,    2, 0x08,   37 /* Private */,
      38,    0,  264,    2, 0x08,   38 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QPoint,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_pushButtonLogin_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonRegister_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonSelectFile_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonUpload_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonFlush_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ListViewCloudDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_ListViewCloudRightClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'on_pushButtonUploadFunction_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonCloudFunction_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonLogout_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonBackFromUpload_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonBackFromCloud_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonManageFunction_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonBackFromManage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonDownload_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonDelete_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonShare_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonCancelShare_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonShareFunction_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonFlushShare_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonCollect_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonBackFromShare_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_ListViewShareDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_pushButtonImageEditorFunction_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonBackFromEditor_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonOpenImage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonSaveImage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonRotateLeft_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonRotateRight_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonFlipH_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonFlipV_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonCrop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonFilter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonAdjust_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButtonReset_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButtonLogin_clicked(); break;
        case 1: _t->on_pushButtonRegister_clicked(); break;
        case 2: _t->on_pushButtonSelectFile_clicked(); break;
        case 3: _t->on_pushButtonUpload_clicked(); break;
        case 4: _t->on_pushButtonFlush_clicked(); break;
        case 5: _t->on_ListViewCloudDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 6: _t->on_ListViewCloudRightClicked((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 7: _t->on_pushButtonUploadFunction_clicked(); break;
        case 8: _t->on_pushButtonCloudFunction_clicked(); break;
        case 9: _t->on_pushButtonLogout_clicked(); break;
        case 10: _t->on_pushButtonBackFromUpload_clicked(); break;
        case 11: _t->on_pushButtonBackFromCloud_clicked(); break;
        case 12: _t->on_pushButtonManageFunction_clicked(); break;
        case 13: _t->on_pushButtonBackFromManage_clicked(); break;
        case 14: _t->on_pushButtonDownload_clicked(); break;
        case 15: _t->on_pushButtonDelete_clicked(); break;
        case 16: _t->on_pushButtonShare_clicked(); break;
        case 17: _t->on_pushButtonCancelShare_clicked(); break;
        case 18: _t->on_pushButtonShareFunction_clicked(); break;
        case 19: _t->on_pushButtonFlushShare_clicked(); break;
        case 20: _t->on_pushButtonCollect_clicked(); break;
        case 21: _t->on_pushButtonBackFromShare_clicked(); break;
        case 22: _t->on_ListViewShareDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 23: _t->on_pushButtonImageEditorFunction_clicked(); break;
        case 24: _t->on_pushButtonBackFromEditor_clicked(); break;
        case 25: _t->on_pushButtonOpenImage_clicked(); break;
        case 26: _t->on_pushButtonSaveImage_clicked(); break;
        case 27: _t->on_pushButtonRotateLeft_clicked(); break;
        case 28: _t->on_pushButtonRotateRight_clicked(); break;
        case 29: _t->on_pushButtonFlipH_clicked(); break;
        case 30: _t->on_pushButtonFlipV_clicked(); break;
        case 31: _t->on_pushButtonCrop_clicked(); break;
        case 32: _t->on_pushButtonFilter_clicked(); break;
        case 33: _t->on_pushButtonAdjust_clicked(); break;
        case 34: _t->on_pushButtonReset_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 35;
    }
    return _id;
}
QT_WARNING_POP
