import folium
import webbrowser

from folium.map import Icon
def Parser(filename):
    pts = []
    file = open(filename, "r")
    dummy = file.readline()
    while file:
        point = []
        try:
            lat_line = file.readline().strip()
            lng_line = file.readline().strip()
            dummy = file.readline().strip()
            if lat_line == '' or lng_line == '':
                break
            point.append(float(lat_line))
            point.append(float(lng_line))
        except ValueError as e:
            print(" ")
        pts.append(point)
    file.close()
    return pts

#Draw the map
my_map = folium.Map(
    location = [30.06509364599475, 31.277267393092313], 
    zoom_start=30
)
pts = Parser("500putty12&%T.txt")
i = 0
for point in pts:
    folium.CircleMarker(point,
                popup='<strong>Step </strong>' + str(i + 1), 
                tooltip='Click for more info', radius=0.5
                ).add_to(my_map)
    i = i + 1
my_PolyLine=folium.PolyLine(locations=pts,weight=1)
my_map.add_child(my_PolyLine)

my_map.save("gps_map.html")
webbrowser.open_new_tab('gps_map.html')