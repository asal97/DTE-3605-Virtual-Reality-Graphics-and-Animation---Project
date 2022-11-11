extends KinematicBody

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

func initialize(start_position,orientation,radius):
	var wr = 0.25
	if(-20.0 < orientation and orientation < 20.0):
		print("left")
		transform.origin = Vector3(start_position[0]-radius-wr,start_position[1],start_position[2])
	elif(-100.0< orientation and orientation < -60.0):
		print("down")
		transform.origin = Vector3(start_position[0],start_position[1],start_position[2]+radius+wr)
	elif((150.0< orientation and orientation< 200.0) or (-150.0 > orientation and orientation> -200.0)):
		print("right")
		transform.origin = Vector3(start_position[0]+radius+ wr,start_position[1],start_position[2])
	else:
		print("up")
		transform.origin = Vector3(start_position[0],start_position[1],start_position[2]-radius-wr)

