X-Watcher
---------

One more (pure) C file handling lib, all contained within a single header file

### What does it (or doesn't) support?

 * [x] Microsoft Windows (starting from XP)
 * [ ] macOS via kqueue
 * [x] Linux via inotify
 * [x] Directory watching
 * [x] File watching
 * [x] Asyncronous watching
 * [x] Symlink support
 * [ ] Remote directory support (not tested, may work)
 * [ ] Regex/Glob watching
 * [ ] Recursive watching
 * [ ] Local directories (Full paths ONLY, for now)
 * [x] Header-only library
 * [x] Written in pure C. No linking with C++ nonsense.

### How do I add it to my project?

Include ```-lpthread``` in your linker and add the following two files
in your project's sources:
 * [array.h](array.h) - as an hard dependency to ```x-watcher.h```
 * [x-watcher.h](x-watcher.h)

### How do I use it?

Look inside [example.c](example.c) and everything should be pretty clear.

Unless you didn't get it for some reason, there are 5 different functions and
three data types to worry about.

#### Structures/Data types:

 * ```x_watcher``` - The structure through which you'll interact with your
 X-Watcher instance. **No touchies**, the data inside it is quite sensitive.
 * ```xWatcher_reference``` - used for defining what xWatcher will look for and
 how it will react when a event hits your desired file or directory.
```C
typedef struct xWatcher_reference {
	// path to the directory or file that's going to be "watched"
	char *path;

	// callback function through which you'll get notified of xwatcher events
	// in classic C, it'll look like this:
	// void callback_func(XWATCHER_FILE_EVENT event, const char *path, int context, void *data) {
	// ...  // lotta code ;)
	// } <- you can name your callback function however you'd like
	void (*callback_func)(
			XWATCHER_FILE_EVENT event,  // the event that occured
			const char *path,           // what file was that (full-path)
			int context,                // where context is going to be returned
			void *additional_data);     // in case you need to pass a global reference or something

	// used by YOUR CODE to provide additional context (if needed)
	int context;

	// in case you need to pass through additional data, such as a global reference
	void *additional_data;
} xWatcher_reference;
```


 * ```XWATCHER_FILE_EVENT``` - Used to determine what happened to your desired
 file or directory.

Since this program supports two backends: inotify and WinAPI, some features
 will be constrained to one or the other.

| Event name                       | What it means?                                | inotify            | Windows            |
|----------------------------------|-----------------------------------------------|--------------------|--------------------|
| XWATCHER_FILE_UNSPECIFIED        | Unspecified event, most likely and issue.     | :heavy_check_mark: | :heavy_check_mark: |
| XWATCHER_FILE_REMOVED            | File or directory has been removed.           | :heavy_check_mark: | :heavy_check_mark: |
| XWATCHER_FILE_CREATED            | File or directory has been created.           | :heavy_check_mark: | :heavy_check_mark: |
| XWATCHER_FILE_MODIFIED           | File or directory has been modified.          | :heavy_check_mark: | :heavy_check_mark: |
| XWATCHER_FILE_OPENED             | A program has opened this file/directory.     | :heavy_check_mark: |                    |
| XWATCHER_FILE_ATTRIBUTES_CHANGED | Ownership, permissions or dates were changed. | :heavy_check_mark: |                    |
| XWATCHER_FILE_NONE               | No events what-so-ever occured.               | :heavy_check_mark: | :heavy_check_mark: |
| XWATCHER_FILE_RENAMED            | File or directory has been renamed.           |                    | :heavy_check_mark: |


#### Functions:


 * ```C
   x_watcher *xWatcher_create(void);
   ```

 Creates the xWatcher instance/object
 
 * ```bool xWatcher_appendFile(x_watcher *watcher, xWatcher_reference *reference)```

 Takes care of adding a single file to the watch structure using the paramaters
 defined in the ```xWatcher_reference``` struct.

 Return value is determines whether the xWatcher failed
 ```(true == all ok, false == fail)```

 * ```bool xWatcher_appendDir(x_watcher *watcher, xWatcher_reference *reference)```

 Just like ```appendFile``` takes care of adding a directory to the watcher.

 Same deal with it's return value ```(true == "all ok", false == "fail")```

 * ```bool xWatcher_start(x_watcher *watcher);```

 Starts the watcher in the background (spawns a new thread).

 WILL leak memory and (possibly) hang the program if left unchecked,
 hence ```xWatcher_destroy``` exists.

 * ```void xWatcher_destroy(x_watcher *watcher);```

 Destroys the watcher instance and frees up any resources used.

### License
```
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004
 
Copyright (C) 2021 Nikola Pavlica <pavlica.nikola at gmail dot com>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.
 
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.
```


### Additional credits

 * A friend on discord who wrote the array libary.
