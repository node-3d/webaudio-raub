'use strict';

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const context = new AudioContext();
	
	const clip = await read(`${__dirname}/samples/hit.wav`);
	
	const musicClip = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	const gain = context.createGain();
	gain.gain.value = 0.0625;
	gain.connect(context.destination);
	
	
	let isActive;
	let i = 1;
	
	// Let it settle down
	await new Promise(res => setTimeout(res, 1000));
	
	setInterval(async () => {
		
		if (isActive) {
			console.log('STILL ACTIVE!');
		}
		isActive = true;
		
		const musicClipNode = context.createBufferSource();
		
		musicClipNode.buffer = musicClip;
		musicClipNode.connect(gain);
		
		musicClipNode.on('ended', () => isActive = false);
		musicClipNode.on('ended', () => console.log('Ended:', i++));
		
		musicClipNode.start(0);
		
	}, 200).unref();
	
	// 60 sec
	await new Promise(res => setTimeout(res, 600000));
	
	console.log('DONE');
	
} catch (e) { console.error(e); } })();
