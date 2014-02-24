//---------------------------------------------------------------------------
// Casing for the Microboard IO Dock
//---------------------------------------------------------------------------
// 24-Feb-2014 ShaneG
//
// A basic holder for the IO dock. This simply keeps it safe from short
// circuiting on the bench.
//---------------------------------------------------------------------------

//--- Dimensions of the PCB
PCB_WIDTH  = 121;
PCB_HEIGHT = 56;
PCB_DEPTH  = 2;

//--- Borders and spacing
BORDER_SIZE = 3;
BORDER_LIP  = 2;
CASE_DEPTH  = 5;

// Create the main block
difference() {
  cube(size = [ PCB_WIDTH + (2 * BORDER_SIZE), PCB_HEIGHT + (2 * BORDER_SIZE), CASE_DEPTH ], center = false);
  // Cut away the hole for the PCB itself
  translate(v = [ BORDER_SIZE, BORDER_SIZE, CASE_DEPTH - PCB_DEPTH ]) {
    cube(size = [ PCB_WIDTH, PCB_HEIGHT, 2 * PCB_DEPTH ], center = false);
    }
  // Cut away the main body
  translate(v = [ BORDER_SIZE + BORDER_LIP, BORDER_SIZE + BORDER_LIP, -CASE_DEPTH ]) {
    cube(size = [ PCB_WIDTH - (2 * BORDER_LIP), PCB_HEIGHT - (2 * BORDER_LIP), 2 * CASE_DEPTH ], center = false);
    }
  }

