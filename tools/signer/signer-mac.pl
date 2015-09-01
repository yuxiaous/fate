#!/usr/bin/perl

#dev.360.cn

use Getopt::Long;
use Term::ANSIColor qw(:constants);
$Term::ANSIColor::AUTORESET=1;

GetOptions(    
	'keystore=s'     => \$keystore,    
	'p1=s'   => \$keypass,    
	'p2=s' => \$storepass,
	'src_dir=s'      => \$src_dir,    
	'dst_dir=s'      => \$dst_dir,
	'alias=s'	 => \$alias
);

sub usage(){
    
    print "\n[-keystore|-k]   : The path of your keystore file\n";
    print "[-keypass|-p2]   : The password of the alias\n";
    print "[-storepass|-p1] : The password of the keystore file\n";
    print "[-src_dir|-s]    : The source directory of your apk files\n";
    print "[-dst_dir|-d]    : The destinate output directiory of your signed apk files\n";
    print "[-alias|-a]      : The alias of the keystore file\n\n";

    print "    ************************************************************\n";
    print "    example: perl signer.pl -k ./test.keystore -p1 1234 -a *.keystore -p2 1234 -s ./apk -d ./apk-d\n\n";

}

#sub generate_keystore_alias(){
    
#    my $kstore_alias = $1 if ($keystore =~ /.*\/(.*\.keystore)$/);
#    if ($kstore_alias eq ""){
#	print BOLD RED "please check the keystore path format, use \".\/*.keystore\" format !\n";
#    }
#    return $kstore_alias;
#}

sub generate_signed_apk{
    
    my $ori_apk = shift @_;
    my $sign_prefix = $1 if ($ori_apk =~ /(.*)\.[aA][pP][kK]$/);

    return $sign_prefix."\_signed\.apk";
    
}

sub generate_aligned_apk{

    my $ori_apk = shift @_;
    my $aligned_prefix = $1 if ($ori_apk =~ /.*\/(.*)\.[aA][pP][kK]$/);
 
    return $dst_dir."\/".$aligned_prefix."\_signed\_aligned\.apk";
}

sub del_sig{

    my $ori_apk = shift;
    my $zip =  "./tools/bin/7za -tzip -ssc d $ori_apk \"META-INF\" ";
    
	`chmod 777 ./tools/bin/7za`;
	my $ret = `$zip`;

    if( $ret =~ /.*Everything is Ok.*/ ){
	#print "delete original signature file success!\n";
  	return 1;
    }else{
	return 0;
    }
}


sub sign_error_msg{

    my $ori_apk    = shift;
    my $signed_apk = shift;

    my $jarsigner = "./tools/bin/jarsigner -verbose -keystore $keystore -storepass $storepass -keypass $keypass -signedjar $signed_apk $ori_apk \"$alias\" ";

	`chmod 777 ./tools/bin/jarsigner`;
    my $ret_str =  `$jarsigner`;

    if($ret_str =~ /.*AndroidManifest.xml.*/){
		pass;
	} else {
		print BOLD RED $ret_str;
	}

    #if ( $ret_str =~ /.*password was incorrect.*/ ){
    #     print BOLD RED"-p1 error, pwrong password input!\n";

    #}elsif( $ret_str =~ /.*key associated with .* not a private key.*/ ){
    #     print BOLD RED"-p2 error, pwrong password input!\n";

    #}elsif( $ret_str =~ /.*unable to open jar file\:\s.*/ ){
    #     print BOLD RED"please input original apk file!\n";

    #}elsif( $ret_str =~ /.*Certificate chain not found for\:\s.*/ ){
    #     print BOLD RED"-a error, please check whether your alias name is correct or not!\n";

    #}elsif( $ret_str =~ /.*keystore load\:\s.*No such file or directory.*/ ){
    #     print BOLD RED"please check your keystore path!\n";
    #}	

    my $pos = index($ret_str, "jar signed");
    if( $pos ne -1 ){
	print "signed $ori_apk success!\n";
	return 1;
    }else{
	return 0;
    }
}

sub align{

    my $signed_apk  = shift;
    my $aligned_apk = shift;

    my $aligned = "./tools/bin/zipalign -f -v 4 $signed_apk $aligned_apk";

	`chmod 777 ./tools/bin/zipalign`;
    my $ret_str = `$aligned`;	

    my $pos = index($ret_str, "Verification succesful");
    if( $pos ne -1){
	print "aligned $signed_apk success!\n";
        return 1;
    }else{
	return 0;
    }
}

sub signer{

    my $apk_name = shift @_;

    my $signed_apk   = generate_signed_apk($apk_name);
    my $aligned_apk  = generate_aligned_apk($apk_name);
    #my $alias        = generate_keystore_alias();

    print BOLD YELLOW"************** http://jiagu.360.cn ***************\n";
    my $del_ret = del_sig($apk_name);
    if( $del_ret ne 0 ){
       `chmod 777 $apk_name`;
    }

    my $sign_ret = sign_error_msg($apk_name, $signed_apk);
    if($sign_ret ne 0){
       `chmod 777 $signed_apk`;
    }
    
    my $align_ret = align($signed_apk, $aligned_apk);
    if( $align_ret ne 0 ){
       `rm -rf $signed_apk`;
       `chmod 777 $aligned_apk`;    
       print BOLD BLUE"$aligned_apk generated!\n";
    }
}

sub find_dir_apk(){

    my $tmp_dir = $src_dir."\/\*";
     
    if( $keystore eq "" || $keypass eq "" || $storepass eq ""  || $src_dir eq "" || $dst_dir eq "" || $alias eq ""){
		usage();
		return;
    }
    if( -d $src_dir ){
		pass;
    } elsif( $src_dir =~ /.*\.[aA][pP][kK]$/ ) {
		if (-e $dst_dir){
			`chmod 777 $dst_dir`;
			signer($src_dir);
			return;
		}else{
            `mkdir $dst_dir`;
			`chmod 777 $dst_dir`;
			signer($src_dir);
			return;
		}
    }
	
    if( -e $src_dir ){
	
		my @dir = glob($tmp_dir);
		foreach my $package (@dir){
			if (-e $dst_dir){
				`chmod 777 $dst_dir`;
				signer($package);
    	    }else{
                `mkdir $dst_dir`;
				`chmod 777 $dst_dir`;
				signer($package);
            }
        }
    }else{
		print BOLD RED "please check the source directory!\n";
    }
}

find_dir_apk();
