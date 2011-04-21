.PHONY: clean All

All:
	@echo ----------Building project:[ kiku - Release - Alsa ]----------
	@cd "kiku" && "$(MAKE)" -f "kiku.mk"
clean:
	@echo ----------Cleaning project:[ kiku - Release - Alsa ]----------
	@cd "kiku" && "$(MAKE)" -f "kiku.mk" clean
