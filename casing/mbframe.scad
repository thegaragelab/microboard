//---------------------------------------------------------------------------
// Simple frame to hold a Microboard format PCB
//---------------------------------------------------------------------------
// 04-Jan-2013 ShaneG
//
//   First version. This is just a simple frame that keeps the board away
//   from any underlying surface - it is not a fully enclosed case.
//---------------------------------------------------------------------------

// Board size
PCB_WIDTH  = 40;
PCB_HEIGHT = 50;
PCB_DEPTH  = 1.5;

// Clip sizes
//
//  There are three clips in total - one at the base and two on each side. They
//  are placed so they provide enough support without interfering with the
//  components mounted on the board. The side clips are CLIP1 and the base clip
//  is CLIP2.
//
//  +-------+
//  |       |
//  []     []
//  []     []
//  |       |
//  |       |
//  |       |
//  +--===--+

CLIP1_SIZE   = 3;
CLIP1_OFFSET = 34;

CLIP2_SIZE   = 10;
CLIP2_OFFSET = 15;

CLIP_HEIGHT  = 10;
CLIP_DEPTH   = 2;
CLIP_WIDTH   = 6;

difference() {
  union() {
    // Create the base plate
    difference() {
      translate(v = [ -(CLIP_WIDTH - CLIP_DEPTH), -(CLIP_WIDTH - CLIP_DEPTH), 0 ]) {
        cube(size = [ PCB_WIDTH + 2 * (CLIP_WIDTH - CLIP_DEPTH), PCB_HEIGHT + 2 * (CLIP_WIDTH - CLIP_DEPTH), PCB_DEPTH ], center = false);
        }
      translate(v = [ CLIP_DEPTH, CLIP_DEPTH, -PCB_DEPTH ]) {
        cube(size = [ PCB_WIDTH - 2 * CLIP_DEPTH, PCB_HEIGHT - 2 * CLIP_DEPTH, PCB_DEPTH * 3 ], center = false);
        }
      }
    // Add the clips
    translate(v = [ -(CLIP_WIDTH - CLIP_DEPTH), CLIP1_OFFSET, 0 ]) {
      cube(size = [ CLIP_WIDTH, CLIP1_SIZE, CLIP_HEIGHT ], center = false);
      }
    translate(v = [ PCB_WIDTH - CLIP_DEPTH, CLIP1_OFFSET, 0 ]) {
      cube(size = [ CLIP_WIDTH, CLIP1_SIZE, CLIP_HEIGHT ], center = false);
      }
    translate(v = [ CLIP2_OFFSET, -(CLIP_WIDTH - CLIP_DEPTH), 0 ]) {
      cube(size = [ CLIP2_SIZE, CLIP_WIDTH, CLIP_HEIGHT ], center = false);
      }
    }
  // Cut out the PCB itself
  translate(v = [ 0, 0, CLIP_HEIGHT - CLIP_DEPTH - PCB_DEPTH ]) {
    cube(size= [ PCB_WIDTH, PCB_HEIGHT, PCB_DEPTH ]);
    }
  }

