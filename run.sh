# CD to gmi2html directory
cd "$(dirname "$0")"

# Convert Gemini capsule pages to HTML
./gmi2html_allauto.sh ../pages
git clone "https://github.com/sneedgroup-holder/nm2.0" wwwsite

# Add our main webpages
cp -r wwwsite/* ../pages
rm -rf wwwsite/

# Make a WAP2.0 version of log
cp ../pages/log/index.html ../pages/log/index.wml
sed -i 's|<!DOCTYPE html><html><head><meta charset="utf-8"><meta http-equiv="Content-Security-Policy" content="upgrade-insecure-requests"><meta name="viewport" content="width=device-width, initial-scale=1.0"><link type="text/css" rel="stylesheet" href="/style.css"><link type="text/css" rel="stylesheet" href="style.css">|<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd"><html><head><meta http-equiv="Content-Type" content="application/vnd.wap.xhtml+xml; charset=UTF-8" />|g' ../pages/log/index.wml

# Make log use scrapeguard
mv "../pages/log/index.html" "../pages/log/index-notabot.html"
git clone https://github.com/Sneed-Group/scrapeguard
cp -r scrapeguard/* ../pages/log
