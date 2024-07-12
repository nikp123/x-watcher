#include "x-watcher.h"

void callback_func(XWATCHER_FILE_EVENT event,
		const char *path, int context, void *data) {

	switch(event) {
		case XWATCHER_FILE_UNSPECIFIED:
			printf("Unspecified event for ");
			break;
		case XWATCHER_FILE_CREATED:
			printf("File creation event for ");
			break;
		case XWATCHER_FILE_REMOVED:
			printf("File removal event for ");
			break;
		case XWATCHER_FILE_OPENED:
			printf("File open event for ");
			break;
		case XWATCHER_FILE_ATTRIBUTES_CHANGED:
			printf("File attribute changed event for ");
			break;
		case XWATCHER_FILE_MODIFIED:
			printf("File modification event for ");
			break;
		case XWATCHER_FILE_RENAMED:
			printf("File renaming event for ");
			break;
		default:
			printf("Unhandled event for ");
			break;
	}

	printf("%s with context %d\n", path, context);
}

int main(int argc, char *argv[]) {
	x_watcher *watcher = xWatcher_create();

	xWatcher_reference dir;
	dir.path = argc > 1 ? argv[1] : "C:\\Users\\nikp123\\Desktop\\asdf.txt";
	dir.callback_func = callback_func;
	dir.context = 1;

	xWatcher_appendFile(watcher, &dir);

	xWatcher_start(watcher);

	getchar();

	xWatcher_destroy(watcher);

	return 0;
}
