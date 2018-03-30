'use strict';

const fs   = require('fs');


module.exports = file => new Promise(
	(res, rej) => fs.readFile(
		file,
		(err, data) => err ? rej(err) : res(data)
	)
);
