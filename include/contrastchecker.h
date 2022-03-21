#ifndef CONTRASTCHECKER_H
#define CONTRASTCHECKER_H

#include <QString>

class ContrastChecker {
public:
    ContrastChecker();

    void hexToRgb( const QString& colorHex );
    qreal luminance( const QString& colorHex );
    bool calcRatio( const QString& colorName );
};

#endif // CONTRASTCHECKER_H
