'use strict';

const fs = require('fs');

const { AudioContext } = require('..');


(async () => { try {
	
	const context = new AudioContext();
	
	const cello = await new Promise((res, rej) => fs.readFile(
		'samples/cello_pluck/cello_pluck_As0.wav',
		(err, data) => err ? rej(err) : res(data)
	));
	
	const audioClip = context.decodeAudioData(cello);
	const audioClipNode = context.createBufferSource();
	audioClipNode.buffer = audioClip;
	
	const pingping = context.createDelay();
	pingping.delayTime.value = 120;
	pingping.connect(context.destination);
	
	audioClipNode.connect(pingping);
	audioClipNode.start(0);
	
	// 10 sec
	await new Promise(res => setTimeout(res, 10000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
