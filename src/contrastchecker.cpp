#include "include/contrastchecker.h"

#include <math.h>

#include <QColor>
#include <QString>
#include <QDebug>
#include <QFile>

namespace {
constexpr const char* SHORTHANDREGEX = "/^#?([a-f\\d])([a-f\\d])([a-f\\d])$/";
}

ContrastChecker::ContrastChecker() {}

void ContrastChecker::hexToRgb( const QString& colorHex ) {
    QColor color( colorHex );
    int red = color.red();
    int green = color.green();
    int blue = color.blue();

    qInfo() << red << green << blue;
}

qreal ContrastChecker::luminance( const QString& colorHex ) {
    QColor color( colorHex );

    qreal corRed = color.red();
    qreal corGreen = color.green();
    qreal corBlue = color.blue();

    corRed /= 255;
    corGreen /= 255;
    corBlue /= 255;

    corRed = corRed <= 0.03928 ? corRed / 12.92 : pow( ( corRed + 0.055 ) / 1.055, 2.4 );
    corGreen = corGreen <= 0.03928 ? corGreen / 12.92 : pow( ( corGreen + 0.055 ) / 1.055, 2.4 );
    corBlue = corBlue <= 0.03928 ? corBlue / 12.92 : pow( ( corBlue + 0.055 ) / 1.055, 2.4 );

    qreal resultado = corRed * 0.2126 + corGreen * 0.7152 + corBlue * 0.0722;
    return resultado;
}

bool ContrastChecker::calcRatio( const QString& colorName ) {
    QList<qreal> textosLuminance;
    textosLuminance.insert( 0, luminance( "#000000" ) );
    textosLuminance.insert( 1, luminance( "#FFFFFF" ) );
    textosLuminance.insert( 2, luminance( "#BBBBBB" ) );

    qreal fundo = luminance( colorName );

    for ( qreal luminance: textosLuminance ) {
        qreal ratio = luminance > fundo
                      ? ( ( fundo + 0.05 ) / ( luminance + 0.05 ) )
                      : ( ( luminance + 0.05 ) / ( fundo + 0.05 ) );

        if ( ratio > 0.33333 ) {
            qInfo() << "[RATIO]" << QString::number( ratio ) << "[FALSE]";
            return false;
        }
    }

    qInfo() << "[RATIO]" << "[TRUE]";

    QString filename="/home/andre/workspace/ColorContrastChecker/data.txt";
    QFile file( filename );
    if ( file.open( QIODevice::WriteOnly | QIODevice::Append ) ) {
        QTextStream stream( &file );
        stream << colorName << endl;
    }

    return true;
}
