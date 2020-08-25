var pipe = require('../');
var os = require('os');
var fs = require('fs');
var path = require('path');
var crypto = require('crypto');

function checkPipeSync(obj, test) {
	var rstat = fs.fstatSync(obj.readfd);
	test.ok(rstat.isFIFO());
	var wstat = fs.fstatSync(obj.writefd);
	test.ok(wstat.isFIFO());

  const msg = "testmsg";
  const buf = Buffer.alloc(msg.length);
  fs.writeSync(obj.writefd, msg);
  fs.readSync(obj.readfd, buf);
  test.strictEqual(msg, buf.toString());
};

module.exports = {
	setUp: function(cb) {
		this.tmppath = path.join(
			os.tmpdir(),
			'.node-pipe.tmp.' + Date.now() + '.' + crypto.randomBytes(8).toString('hex')
		);

		cb();
	},
	tearDown: function(cb) {
		try {
			fs.unlinkSync(this.tmppath);
		} catch (e) {

		}

		cb();
	},
  pipeSync: function(test) {
    let obj = pipe.pipeSync();
    checkPipeSync(obj, test);

    test.done();
  }
}
