'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	
	const clip = await read(`${__dirname}/samples/hit.wav`);
	
	const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	
	const musicClipNode = context.createBufferSource();
	
	
	musicClipNode.buffer = musicClip;
	musicClipNode.connect(gain);
	
	gain.connect(context.destination);
	
	
	let isActive;
	let startTime;
	
	musicClipNode.on('ended', () => isActive = false);
	
	setInterval(() => {
		if (isActive) {
			console.log('STILL ACTIVE!');
		}
		isActive = true;
		startTime = Date.now();
		musicClipNode.start(0);
	}, 500);
	
	
	// 60 sec
	await new Promise(res => setTimeout(res, 600000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();

