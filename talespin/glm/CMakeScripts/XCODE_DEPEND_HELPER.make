# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# For each target create a dummy rule so the target does not have to exist


# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glm.Debug:
/Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/Debug/glm:
	/bin/rm -f /Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/Debug/glm


PostBuild.glm.Release:
/Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/Release/glm:
	/bin/rm -f /Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/Release/glm


PostBuild.glm.MinSizeRel:
/Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/MinSizeRel/glm:
	/bin/rm -f /Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/MinSizeRel/glm


PostBuild.glm.RelWithDebInfo:
/Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/RelWithDebInfo/glm:
	/bin/rm -f /Users/Amaru/Desktop/Aktuellt_skolarbete/Luftens\ Hjältar/talespin/glm/RelWithDebInfo/glm


