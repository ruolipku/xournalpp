/*
 * Xournal++
 *
 * Base class for prviews in the sidebar
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include "gui/sidebar/AbstractSidebarPage.h"

#include <XournalType.h>

#include <gtk/gtk.h>

class PdfCache;
class SidebarLayout;
class SidebarPreviewPage;
class SidebarToolbar;

class SidebarPreviewBase : public AbstractSidebarPage
{
public:
	SidebarPreviewBase(Control* control);
	virtual ~SidebarPreviewBase();

public:
	/**
	 * Layout the pages to the current size of the sidebar
	 */
	void layout();

	/**
	 * Update the preview images
	 */
	void updatePreviews();

	/**
	 * @overwrite
	 */
	virtual bool hasData();

	/**
	 * @overwrite
	 */
	virtual GtkWidget* getWidget();

	/**
	 * Setts the Background of the panel white, before the first draw
	 */
	void setBackgroundWhite();

	/**
	 * Gets the zoom factor for the previews
	 */
	double getZoom();

	/**
	 * Gets the PDF cache for preview rendering
	 */
	PdfCache* getCache();

public:
	// DocumentListener interface
	virtual void documentChanged(DocumentChangeType type);
	virtual void pageSizeChanged(int page);
	virtual void pageChanged(int page);
	virtual void pageInserted(int page);
	virtual void pageDeleted(int page);
	virtual void pageSelected(int page);

private:
	/**
	 * Timeout callback to scroll to a page
	 */
	static bool scrollToPreview(SidebarPreviewBase* sidebar);

	/**
	 * The size of the sidebar has chnaged
	 */
	static void sizeChanged(GtkWidget* widget, GtkAllocation* allocation, SidebarPreviewBase* sidebar);
private:
	XOJ_TYPE_ATTRIB;

	/**
	 * The widget within the scrollarea with the page icons
	 */
	GtkWidget* iconViewPreview;

	/**
	 * The scrollbar with the icons
	 */
	GtkWidget* scrollPreview;

	/**
	 * The Table with the Toolbar and the Scrollbar
	 */
	GtkTable* table;

	/**
	 * The previews
	 */
	SidebarPreviewPage** previews;
	int previewCount;

	/**
	 * The currently selected page
	 */
	int selectedPage;

	/**
	 * The Zoom of the previews
	 */
	double zoom;

	/**
	 * Only once, see setBackgroundWhite()
	 */
	bool backgroundInitialized;

	/**
	 * For preview rendering
	 */
	PdfCache* cache;

	/**
	 * The layouting class for the prviews
	 */
	SidebarLayout* layoutmanager;

	/**
	 * The Toolbar to move, copy & delete pages
	 */
	SidebarToolbar* toolbar;

	friend class SidebarLayout;
};