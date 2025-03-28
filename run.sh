cd "$(dirname "$0")"

./gmi2html_allauto.sh ../pages
git clone "https://github.com/sneedgroup-holder/nm2.0" wwwsite
cp -r wwwsite/* ../pages
rm -rf wwwsite/
cp ../pages/log/index.html ../pages/log/index.wml
sed -i 's|<!DOCTYPE html><html><head><meta charset="utf-8"><meta http-equiv="Content-Security-Policy" content="upgrade-insecure-requests"><meta name="viewport" content="width=device-width, initial-scale=1.0"><link type="text/css" rel="stylesheet" href="/style.css"><link type="text/css" rel="stylesheet" href="style.css">|<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE html PUBLIC "-//WAPFORUM//DTD XHTML Mobile 1.2//EN" "http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd"><html><head><meta http-equiv="Content-Type" content="application/vnd.wap.xhtml+xml; charset=UTF-8" />|g' ../pages/log/index.wml
