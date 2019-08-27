'use strict';

const fs = require('fs');
const { bin } = require('addon-tools-raub');


const copy = (src, dest) => new Promise(
	(res, rej) => fs.copyFile(src, dest, err => (err ? rej(err) : res()))
);


const exists = name => new Promise(
	res => fs.access(
		name,
		fs.constants.F_OK,
		err => res(err ? false : true)
	)
);


const mkdir = async name => {
	if (await exists(name)) {
		return;
	}
	return new Promise(
		(res, rej) => fs.mkdir(name, err => (err ? rej(err) : res()))
	);
};


const rm = async name => {
	if ( ! await exists(name) ) {
		return;
	}
	await new Promise(
		(res, rej) => fs.unlink(name, err => (err ? rej(err) : res()))
	);
};


(async () => {
	
	const binAbs = `${__dirname}/../${bin}`;
	
	if ( ! await exists(binAbs) ) {
		await mkdir(binAbs);
	}
	
	const destAbs = `${binAbs}/webaudio.node`;
	
	if (await exists(destAbs)) {
		await rm(destAbs);
	}
	
	await copy(`${__dirname}/build/Release/webaudio.node`, destAbs);
	
	console.log(`The binary was copied to "${bin}".`);
	
})();
