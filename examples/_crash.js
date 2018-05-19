'use strict';

var SegfaultHandler = require('segfault-handler');
 
SegfaultHandler.registerHandler('crash.log');

const { AudioContext } = require('..');

const read = require('./utils/read');


const GC_LOCK = { _i: 0 };
let num = 0;
(async () => { try {
	
	const count = 6;
	const objects = [];
	const scene = [];
	
	const context = new AudioContext();
	
	const clip = await read(`${__dirname}/samples/hit.wav`);
	
	// const gain = context.createGain();
	// gain.connect( context.destination );
	
	const buffer = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	// GC_LOCK.objects = objects;
	// GC_LOCK.scene = scene;
	// GC_LOCK.context = context;
	// GC_LOCK.clip = clip;
	// GC_LOCK.gain = gain;
	// GC_LOCK.buffer = buffer;
	
	// Create objects when audio buffer is loaded
	for (let i = 0; i < count; i++) {
		const ball = { y: 0 };
		const audio = {};
		audio.panner = context.createPanner();
		audio.panner.connect( context.destination );
		audio.isPlaying = false;
		audio.startTime = 0;
		audio.playbackRate = 1;
		audio.play = () => {
			if ( audio.isPlaying === true ) {
				
				console.warn( 'Audio is already playing.' );
				return;
				
			}
			
			var source = context.createBufferSource();
			
			console.log(Date.now(), '+ABSN:', ++num);
			
			source.buffer = buffer;
			source.onended = () => {
				audio.isPlaying = false;
				console.log(Date.now(), '-ABSN:', --num);
			};
			source.playbackRate.setValueAtTime(audio.playbackRate, audio.startTime);
			audio.startTime = context.currentTime;
			source.start( audio.startTime, 0 );
			
			audio.isPlaying = true;
			
			audio.source = source;
			
			audio.source.connect( audio.panner );
			
		};
		ball.audio = audio;
		scene.push(ball);
		objects.push(ball);
	}
	
	const speed = 0.002;
	const height = 3;
	const offset = 0.5;
	
	const render = () => {
		GC_LOCK._i++;
		
		const time = Date.now();
		for ( let i = 0; i < objects.length; i++ ) {
			const ball = objects[ i ];
			const previousHeight = ball.y;
			const al = i * offset + ( time * speed );
			
			ball.y = Math.abs( Math.sin( al ) * height );
			
			if (ball.y === previousHeight) {
				continue;
			}
			
			if ( ball.y < previousHeight ) {
				ball.down = true;
			} else {
				// If ball changed direction from down to up
				if ( ball.down === true ) {
					
					ball.audio.play();
					ball.down = false;
					
				}
			}
		}
	};
	
	setInterval(() => render(), 16);
	
} catch (e) { console.error(e); } })();
