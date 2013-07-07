/****************************************************************************
** Meta object code from reading C++ file 'compass.h'
**
** Created: Wed Jun 26 00:21:33 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../compass.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'compass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Controler[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   11,   10,   10, 0x0a,
      58,   46,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Controler[] = {
    "Controler\0\0data\0handleControlData(QByteArray)\0"
    "isConnected\0HandleSensorState(bool)\0"
};

const QMetaObject Controler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Controler,
      qt_meta_data_Controler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Controler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Controler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Controler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Controler))
        return static_cast<void*>(const_cast< Controler*>(this));
    return QObject::qt_metacast(_clname);
}

int Controler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: handleControlData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: HandleSensorState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
