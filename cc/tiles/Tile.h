#ifndef Tile_h
#define Tile_h

#include "SkRefCnt.h"
#include "third_party/WebKit/Source/wtf/ThreadingPrimitives.h"
#include "third_party/WebKit/Source/platform/geometry/IntSize.h"
#include "third_party/WebKit/Source/platform/geometry/IntRect.h"
#include "third_party/skia/include/core/SkColor.h"

#include "public/platform/WebTraceLocation.h" // TODO

class SkBitmap;

namespace cc_blink {
class WebLayerImpl;
}

namespace cc {

enum TilePriority {
    TilePriorityWillBeShowed,
    TilePriorityNormal,
};

class TileGrid;

class TileTraceLocation : public blink::WebTraceLocation {
public:
	TileTraceLocation(const char* func, const char* file, bool isRef)
		: blink::WebTraceLocation(func, file)
	{
		m_isRef = isRef;
	}
private:
	bool m_isRef;
};

class Tile {
public:
    const static int kDefaultTileWidth = 160; // weolar 256
    const static int kDefaultTileHeight = 160;

    Tile(TileGrid* tileGrid, int xIndex, int yIndex);
    ~Tile();

	void ref(const blink::WebTraceLocation&);
	void unref(const blink::WebTraceLocation&);
	int32_t getRefCnt() const;

    int xIndex() const { return m_xIndex; }
    int yIndex() const { return m_yIndex; }
    Mutex& mutex() { return m_mutex; }

//     SkBitmap* bitmap() { return m_bitmap; }
//     void clearBitmap();

	bool bitmap() { return m_bitmap; }
	void clearBitmap();

    blink::IntRect postion() const;
    blink::IntRect dirtyRect(); // 以本tile为坐标系
    void appendDirtyRect(const blink::IntRect& r);
    void clearDirtyRect();
    void setAllBoundDirty();
    TilePriority priority() const;
    void setPriority(TilePriority priority);
    void eraseColor(const blink::IntRect& r, const SkColor* color);
    void allocBitmapIfNeeded();

	bool isSameTileGrid(const TileGrid* tileGrid) const;

    cc_blink::WebLayerImpl* layer() const;
    TileGrid* tileGrid() const;

	Vector<TileTraceLocation*>* refFrom() { return &m_refFrom; };

    bool isNotInit() { return m_isNotInit; } // for debug

    void increaseUseingRate();
    size_t usingRate() const { return m_useingRate; }

private:
	mutable int32_t m_refCnt;
    bool m_isNotInit; // for debug

    TileGrid* m_tileGrid;

    int m_xIndex;
    int m_yIndex;
    blink::IntRect m_postion;
    blink::IntRect m_dirtyRect;
    TilePriority m_priority;
    //SkBitmap* m_bitmap;
	bool m_bitmap;
    Mutex m_mutex;
    size_t m_useingRate;
	Vector<TileTraceLocation*> m_refFrom;
};

}

#endif // Tile_h