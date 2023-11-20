'use strict';

const fs = require('fs');


const readAsBuffer = (path) => new Promise(
	(res, rej) => fs.readFile(
		path,
		(err, data) => err ? rej(err) : res(data)
	),
);

module.exports = { readAsBuffer };
