'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	
	const cello = await read(`${__dirname}/samples/voice.ogg`);
	
	const audioClip = await new Promise(res => context.decodeAudioData(cello, b => res(b)));
	const audioClipNode = context.createBufferSource();
	audioClipNode.buffer = audioClip;
	
	const pingping = context.createDelay(3);
	
	pingping.delayTime.value = 3;
	pingping.connect(context.destination);
	
	audioClipNode.connect(pingping);
	audioClipNode.start(0);
	
	// 20 sec
	await new Promise(res => setTimeout(res, 20000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
