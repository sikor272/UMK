import re
tekst = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris vel maximus felis, sed molestie purus. Donec nec consectetur massa. Mauris nec eleifend elit, eu pulvinar erat. In hac habitasse platea dictumst. Pellentesque sit amet sapien eu metus luctus sagittis. Quisque quis hendrerit ligula. Ut vel ligula nec velit semper aliquet. Nullam nisl urna, ullamcorper id risus eu, scelerisque aliquam lacus. Fusce cursus at urna at pharetra. Donec ut elit maximus, finibus mauris cursus, suscipit felis. Donec turpis ex, tempus at tempor eu, tincidunt sit amet augue. Maecenas quis venenatis erat. Sed fermentum eros et purus ultricies placerat. Nullam orci massa, ornare quis dolor sed, blandit finibus tortor. Nam nec dapibus ante.'
x = 0
wyrazenie = raw_input()
p = re.compile(wyrazenie)
for m in p.finditer(tekst):
        print ("Znaleziono:",m.group(),"od pozycji:", m.start(), "do:", m.end())
        x = 1
if x == 0:
        print ("Nie znaleziono ani jednego")


