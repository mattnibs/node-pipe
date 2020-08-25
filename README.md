POSIX pipe(2) for NodeJS

## Installation

```
npm install node-pipe
```

## Example

### Sync

```javascript
var pipeSync = require('unix-pipe').pipeSync

let { readfd, writefd } = pipeSync()
```

### Async

TODO
