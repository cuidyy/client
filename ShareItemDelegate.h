#ifndef SHAREITEMDELEGATE_H
#define SHAREITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>

class ShareItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ShareItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override
    {
        painter->save();

        // 绘制背景
        painter->fillRect(option.rect, Qt::white);
        if (option.state & QStyle::State_MouseOver) {
            painter->fillRect(option.rect, QColor(240, 240, 240));
        }

        // 获取数据
        QPixmap mainImage = index.data(Qt::DecorationRole).value<QPixmap>();
        QString title = index.data(Qt::DisplayRole).toString();
        QString author = index.data(Qt::UserRole + 1).toString();
        QList<QPixmap> thumbnails = index.data(Qt::UserRole + 2).value<QList<QPixmap>>();

        // 计算各个区域的位置
        QRect contentRect = option.rect.adjusted(10, 10, -10, -10);
        
        // 主图区域
        QRect imageRect = contentRect.adjusted(0, 0, 0, -60);
        if (!mainImage.isNull()) {
            QPixmap scaledImage = mainImage.scaled(imageRect.size(), 
                Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QRect actualImageRect = QRect(
                imageRect.x() + (imageRect.width() - scaledImage.width()) / 2,
                imageRect.y() + (imageRect.height() - scaledImage.height()) / 2,
                scaledImage.width(), scaledImage.height()
            );
            painter->drawPixmap(actualImageRect, scaledImage);
        }

        // 缩略图区域
        if (!thumbnails.isEmpty()) {
            int thumbSize = 40;
            int thumbSpacing = 5;
            int thumbY = contentRect.bottom() - 55;
            int startX = contentRect.x();
            
            for (int i = 0; i < qMin(3, thumbnails.size()); ++i) {
                QRect thumbRect(startX + i * (thumbSize + thumbSpacing), 
                              thumbY, thumbSize, thumbSize);
                painter->drawPixmap(thumbRect, 
                    thumbnails[i].scaled(thumbSize, thumbSize, 
                    Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }

        // 标题和作者信息
        QRect textRect = contentRect.adjusted(0, contentRect.height() - 45, 0, 0);
        painter->setPen(Qt::black);
        QFont titleFont = painter->font();
        titleFont.setBold(true);
        painter->setFont(titleFont);
        painter->drawText(textRect, Qt::AlignLeft | Qt::AlignTop, title);

        QFont authorFont = painter->font();
        authorFont.setBold(false);
        painter->setFont(authorFont);
        painter->setPen(QColor(128, 128, 128));
        painter->drawText(textRect.adjusted(0, 20, 0, 0), 
            Qt::AlignLeft | Qt::AlignTop, author);

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override
    {
        return QSize(300, 380);
    }
};

#endif // SHAREITEMDELEGATE_H
