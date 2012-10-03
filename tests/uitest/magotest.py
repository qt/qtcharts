from mago import TestCase
import ldtp
from ldtputils import *
import ldtputils

class TestMinimal(TestCase):
    launcher = '/home/ferdek/charts/bin/release/uitest'
    window_name = 'flrRangeMinDown'

    before = '/tmp/image1.png'
    after = '/tmp/image2.png'

    offsetX = 15
    offsetY = 15
    captureHeight = 200
    captureWidth = 200

    # helper functions
    def capturechartbefore(self):
        ldtp.imagecapture(self.window_name, self.before, self.offsetX, self.offsetY, self.captureWidth, self.captureHeight)

    def capturechartafter(self):
        ldtp.imagecapture(self.window_name, self.after, self.offsetX, self.offsetY, self.captureWidth, self.captureHeight)

    def comparechart(self):
        self.assertTrue(ldtputils.imagecompare(self.before, self.after) > 0)

    # tests
    def test_tickcountchange(self):
        self.capturechartbefore()
        ldtp.click(self.window_name, 'btnTickUp')
        self.capturechartafter()
        self.comparechart()
