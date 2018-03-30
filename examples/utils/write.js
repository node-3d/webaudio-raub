'use strict';

const fs   = require('fs');


module.exports = (file, data) => new Promise(
	(res, rej) => fs.writeFile(
		file,
		data,
		err => err ? rej(err) : res()
	)
);
